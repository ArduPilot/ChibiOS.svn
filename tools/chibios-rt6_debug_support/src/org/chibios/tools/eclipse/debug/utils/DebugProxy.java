/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

package org.chibios.tools.eclipse.debug.utils;

import org.eclipse.cdt.debug.core.cdi.model.ICDITarget;
import org.eclipse.cdt.debug.internal.core.model.CDebugTarget;
import org.eclipse.cdt.debug.mi.core.MIException;
import org.eclipse.cdt.debug.mi.core.MIFormat;
import org.eclipse.cdt.debug.mi.core.MISession;
import org.eclipse.cdt.debug.mi.core.cdi.model.Target;
import org.eclipse.cdt.debug.mi.core.command.CommandFactory;
import org.eclipse.cdt.debug.mi.core.command.MIDataEvaluateExpression;
import org.eclipse.cdt.debug.mi.core.command.MIDataReadMemory;
import org.eclipse.cdt.debug.mi.core.output.MIDataEvaluateExpressionInfo;
import org.eclipse.cdt.debug.mi.core.output.MIDataReadMemoryInfo;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.model.IDebugTarget;

@SuppressWarnings("restriction")
public class DebugProxy {

  private CommandFactory cmd_factory;
  private MISession mi_session;

  private void getSession(CDebugTarget target)
      throws DebugProxyException {
    ICDITarget[] targets = target.getCDISession().getTargets();
    ICDITarget cdi_target = null;
    for (int i = 0; i < targets.length; i++) {
      if (targets[i] instanceof Target) {
        cdi_target = targets[i];
        break;
      }
    }
    if (cdi_target == null)
      throw new DebugProxyException("no CDI session found");
    mi_session = ((Target)cdi_target).getMISession();
    cmd_factory = mi_session.getCommandFactory();
  }

  public DebugProxy()
      throws DebugProxyException {
    IDebugTarget[] targets = DebugPlugin.getDefault().getLaunchManager().getDebugTargets();
    for (IDebugTarget target:targets) {
      if(target instanceof CDebugTarget) {
        getSession((CDebugTarget)target);
        return;
      }
    }
  }

  public DebugProxy(CDebugTarget target)
      throws DebugProxyException {
    getSession(target);
  }

  public long scanStack(long base, long end, long pattern)
      throws DebugProxyException {
    if (mi_session.getMIInferior().isRunning())
      return -1;
    if (end > base) {
      MIDataReadMemory mem = cmd_factory.createMIDataReadMemory(0,
          Long.toString(base),
          MIFormat.HEXADECIMAL,
          4,
          1,
          (int)(end - base),
          '.');
      try {
        mi_session.postCommand(mem);
         MIDataReadMemoryInfo info = mem.getMIDataReadMemoryInfo();
         if (info != null) {
           long[] data = info.getMemories()[0].getData();
           int i = 0;
           while ((i < data.length) && (data[i] == pattern))
               i++;
           return i * 4;
         }
      } catch (MIException e) {}
      throw new DebugProxyException("error reading memory at " +
          base);
    }
    return 0;
  }

  public String evaluateExpression(String expression)
      throws DebugProxyException {
    if (mi_session.getMIInferior().isRunning())
      return null;
    MIDataEvaluateExpression expr = cmd_factory.createMIDataEvaluateExpression(expression);
    try {
      mi_session.postCommand(expr);
      MIDataEvaluateExpressionInfo info = expr.getMIDataEvaluateExpressionInfo();
      if (info != null)
        return info.getExpression();
    } catch (MIException e) {}
    throw new DebugProxyException("error evaluating the expression: '" +
                                  expression + "'");
  }

  public String readCString(long address, int max)
      throws DebugProxyException {
    if (mi_session.getMIInferior().isRunning())
      return null;
    MIDataReadMemory mem = cmd_factory.createMIDataReadMemory(0,
                                                              Long.toString(address),
                                                              MIFormat.HEXADECIMAL,
                                                              1,
                                                              1,
                                                              max,
                                                              '.');
    try {
      mi_session.postCommand(mem);
       MIDataReadMemoryInfo info = mem.getMIDataReadMemoryInfo();
       if (info != null) {
          String s = info.getMemories()[0].getAscii();
          int i = s.indexOf('.');
          if (i >= 0)
            return s.substring(0, s.indexOf('.'));
          else
            return s;
       }
    } catch (MIException e) {}
    throw new DebugProxyException("error reading memory at " +
        address);
  }
}
