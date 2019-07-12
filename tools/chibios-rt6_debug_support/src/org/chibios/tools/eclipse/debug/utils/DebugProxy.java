/********************************************************************************
 * Copyright (c) 2019 Giovanni Di Sirio.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 ********************************************************************************/

package org.chibios.tools.eclipse.debug.utils;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.debug.core.DebugEvent;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.IDebugEventSetListener;
import org.eclipse.debug.core.model.MemoryByte;

import org.eclipse.cdt.dsf.mi.service.MIFormat;
import org.eclipse.cdt.dsf.mi.service.command.output.MIDataReadMemoryInfo;

public class DebugProxy implements IDebugEventSetListener {

  private Object currentSession = null;
  private GDBEventProvider provider = null;
  private List<IGDBInterfaceSuspendListener> suspendListener = new ArrayList<IGDBInterfaceSuspendListener>();
  private List<IGDBInterfaceTerminateListener> terminateListener = new ArrayList<IGDBInterfaceTerminateListener>();

  public DebugProxy() {
    if (!hasActiveDebugSession()) {
        init();
    }
  }

  public void dispose() {
    currentSession = null;
    DebugPlugin.getDefault().removeDebugEventListener(this);
    provider.dispose();
    provider = null;
  }

  public boolean hasActiveDebugSession() {
    if (currentSession == null) {
      return false;
    }
    else {
      return true;
    }
  }

  private void init() {
    DebugPlugin.getDefault().addDebugEventListener(this);
    provider = new GDBEventProvider();
  }

  /**
   * Handle DebugEvents
   */
  @Override
  public void handleDebugEvents(DebugEvent[] events) {
      for (DebugEvent event : events) {

          Object source = event.getSource();
          Object sourceSession = null;
          Object currentSession = GDBSessionTranslator.getSession();
          
          if (source instanceof GDBEventProvider.DebugContextChangedDebugEvent) {
              sourceSession = ((GDBEventProvider.DebugContextChangedDebugEvent) source).getSession();
          } else if (source instanceof GDBEventProvider.DsfSessionDebugEvent) {
              sourceSession = ((GDBEventProvider.DsfSessionDebugEvent) source).getSession();
          } else {
              sourceSession = GDBSessionTranslator.getSession(source);
          }
          
          if (currentSession != this.currentSession) { // Session has changed;
              this.currentSession = currentSession;
              if (this.currentSession != null) { // new session is active and known (Standard/DSF)
                  for (IGDBInterfaceSuspendListener listener : suspendListener)
                      listener.gdbSuspendListener();
              } else { // new session is terminated or unknown
                  for (IGDBInterfaceTerminateListener listener : terminateListener)
                      listener.gdbTerminateListener();
              }
          }
          
          // source session should always be not null and the same as current (do not
          // handle events not from current selected session!)
          if (sourceSession == null || sourceSession != currentSession)
              return;

          if (event.getKind() == DebugEvent.SUSPEND) {
              for (IGDBInterfaceSuspendListener listener : suspendListener)
                  listener.gdbSuspendListener();
          }
          
          if (event.getKind() == DebugEvent.TERMINATE) {
              for (IGDBInterfaceTerminateListener listener : terminateListener)
                  listener.gdbTerminateListener();
          }
          
      }
  }

  protected MemoryByte[] readMemory(long offset, final String address,
                                    int word_format, int word_size,
                                    int rows, int cols,
                                    Character c)
      throws DebugProxyException {

  	MemoryByte[] data = null;

    if (hasActiveDebugSession()) {
      try {
        MIDataReadMemoryInfo meminfo;
      	meminfo = GDBSessionTranslator.readMemory(currentSession,
                                                  offset,
                                                  address,
                                                  word_format,
                                                  word_size,
                                                  rows,
                                                  cols,
                                                  c);
      	data = meminfo.getMIMemoryBlock();
      } catch (Exception e) {
        throw new DebugProxyException("memory reading error: " + e.toString());
      }
    }
      
    return data;
  }

	protected String evaluateExpression(String expression)
			throws DebugProxyException {

		String result = null;
		if (hasActiveDebugSession()) {
			try {
				result = GDBSessionTranslator.evaluateExpression(currentSession,
				                                                 expression);
			}
			catch (Exception e) {
				throw new DebugProxyException("evaluation expression error: "
				    + e.toString());
			}
		}
		return result;
	}

	public long evaluateExpressionNumber(String expression)
			throws DebugProxyException {

		return HexUtils.parseNumber(evaluateExpression(expression));
	}

  protected long scanStack(long base, long end, byte pattern)
      throws DebugProxyException {
    
    if (end > base) {
      try {
      	MemoryByte[] data  = readMemory(0, Long.toString(base),
      	                                MIFormat.HEXADECIMAL,
                                      	4, 1, (int)(end - base), '.');
        int i = 0;
        while ((i < data.length) && (data[i].getValue() == pattern)) {
          i++;
        }
        return i;
      } catch (Exception e) {}
      throw new DebugProxyException("error reading memory at " + base);
    }
    
    return 0;
  }

	protected String readCString(long address,
	                             int max) throws DebugProxyException {

		String result = "";
		try {
			MemoryByte[] data = readMemory(0, Long.toString(address),
			                               MIFormat.HEXADECIMAL, 1, 1, max, '.');
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < data.length; i++) {
				if (data[i].getValue() == 0) {
					break;
				}
				sb.append((char) data[i].getValue());
			}
			result = sb.toString();
		}
		catch (Exception e) {
			throw new DebugProxyException("error reading memory at " + address);
		}
	
	  return result;
	}
}
