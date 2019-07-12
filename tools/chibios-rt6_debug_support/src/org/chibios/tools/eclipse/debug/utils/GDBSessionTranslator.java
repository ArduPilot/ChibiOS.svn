/*******************************************************************************
 * Copyright (c) 2015 EmbSysRegView
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *     edubec - initial API and implementation
 *******************************************************************************/
package org.chibios.tools.eclipse.debug.utils;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.eclipse.cdt.dsf.concurrent.DataRequestMonitor;
import org.eclipse.cdt.dsf.concurrent.ImmediateExecutor;
import org.eclipse.cdt.dsf.concurrent.Query;
import org.eclipse.cdt.dsf.datamodel.IDMContext;
import org.eclipse.cdt.dsf.debug.service.IExpressions;
import org.eclipse.cdt.dsf.debug.service.IExpressions.IExpressionDMContext;
import org.eclipse.cdt.dsf.debug.service.command.ICommand;
import org.eclipse.cdt.dsf.gdb.internal.ui.GdbUIPlugin;
import org.eclipse.cdt.dsf.gdb.launching.GdbLaunch;
import org.eclipse.cdt.dsf.gdb.service.command.IGDBControl;
import org.eclipse.cdt.dsf.mi.service.command.CommandFactory;
import org.eclipse.cdt.dsf.mi.service.command.output.MIDataEvaluateExpressionInfo;
import org.eclipse.cdt.dsf.mi.service.command.output.MIDataReadMemoryInfo;
import org.eclipse.cdt.dsf.service.DsfServicesTracker;
import org.eclipse.cdt.dsf.service.DsfSession;
import org.eclipse.cdt.dsf.ui.viewmodel.datamodel.IDMVMContext;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IProcess;
import org.eclipse.debug.ui.DebugUITools;

@SuppressWarnings("restriction")
public class GDBSessionTranslator {
    /**
     * Get Session Object from current debug context
     * 
     * @return Session Object or null on error
     */
    static public Object getSession() {
        return getSession(DebugUITools.getDebugContext());
    }

    /**
     * Get Session Object from debug context
     * 
     * @return Session Object or null on error
     */
    static public Object getSession(Object context) {
        Object session = null;
        if (null != context) {
            if (context instanceof DsfSession)
                session = context;
            if (context instanceof IProcess) {
                // gets ILaunch out of processes (RuntimeProcess, GDBProcess)
                context = ((IProcess) context).getLaunch();
            }
            if (context instanceof GdbLaunch) {
                // GdbLaunch -> DsfSession
                session = ((GdbLaunch) context).getSession();
            } else if (context instanceof IDMVMContext) {
                // DsfSession
                IDMContext dmc = ((IDMVMContext) context).getDMContext();
                if (null == dmc)
                    return null;
                session = DsfSession.getSession(dmc.getSessionId());
            }
        }
        if (null != session && isSessionTerminated(session))
            return null; // do not return terminated sessions
        return session;
    }

    static public boolean isSessionTerminated(Object session) {
        ILaunch[] launches = DebugPlugin.getDefault().getLaunchManager().getLaunches();
        for (int i = 0; i < launches.length; i++) {
            ILaunch l = launches[i];
            if (session == getSession(l)) {
                return l.isTerminated();
            }
        }
        return true;
    }

    /**
     * Get Session Object out of ILaunch
     * 
     * @param launch
     * @return Session Object or null on error
     */
    static public Object getSession(ILaunch launch) {
        if (null != launch) {
            if (launch instanceof GdbLaunch) {
                // GdbLaunch -> DsfSession
                return ((GdbLaunch) launch).getSession();
            }
        }
        return null;
    }

    public static int maxWaitTimeInInMilliseconds = 5000;
    
    public static String evaluateExpression(Object session, String expression) throws DebugProxyException {
        if (session != null && session instanceof DsfSession) {
            return evaluateExpression((DsfSession) session, expression);
        } else {
            return "";
        }
    }

    public static String evaluateExpression(DsfSession session, String expression) throws DebugProxyException {
        String result = null;
        

        if (session.isActive()) {
            DsfServicesTracker tracker = new DsfServicesTracker(GdbUIPlugin.getBundleContext(), session.getId());
            IExpressions exprService = tracker.getService(IExpressions.class);

            final IGDBControl gdbControl = tracker.getService(IGDBControl.class);

            if (gdbControl != null) {
                MIDataEvaluateExpressionInfo data = null;
                IExpressionDMContext exprContext = exprService.createExpression(gdbControl.getContext(), expression); // $NON-NLS-1$
                CommandFactory commandFactory = gdbControl.getCommandFactory();
                final ICommand<MIDataEvaluateExpressionInfo> exprInfoCommand = commandFactory
                        .createMIDataEvaluateExpression(exprContext);

                Query<MIDataEvaluateExpressionInfo> query = new Query<MIDataEvaluateExpressionInfo>() {
                    @Override
                    protected void execute(final DataRequestMonitor<MIDataEvaluateExpressionInfo> rm) {
                        gdbControl.queueCommand(exprInfoCommand,
                                new DataRequestMonitor<MIDataEvaluateExpressionInfo>(gdbControl.getExecutor(), null) {
                                    @Override
                                    protected void handleCompleted() {
                                        rm.setData(getData());
                                        rm.done();
                                    }
                                });
                    }
                };

                ImmediateExecutor.getInstance().execute(query);

                try {
                    // The Query.get() method is a synchronous call which blocks until the query
                    // completes.
                    data = query.get(maxWaitTimeInInMilliseconds, TimeUnit.MILLISECONDS);
                    if (data.isError()) {
                        data = null;
                    }
                    result = data.getValue();

                } catch (InterruptedException exc) {
                } catch (ExecutionException exc) {
                } catch (TimeoutException e) {
                    throw new DebugProxyException("Timeout happened when evaluating the expression: '" + expression);
                } finally {
                    tracker.dispose();
                }
            }
        }
        return result;
    }
    
    public static MIDataReadMemoryInfo readMemory(Object session, long offset, final String address, int word_format, int word_size, int rows,
            int cols, Character asChar) throws TimeoutException {
        
        if (session != null && session instanceof DsfSession) {
            return readMemory((DsfSession)session, offset, address, word_format, word_size, rows, cols, asChar);
        } else {
            return null;
        }
    }


    public static MIDataReadMemoryInfo readMemory(DsfSession session, long offset, final String address, int word_format, int word_size, int rows,
            int cols, Character asChar) throws TimeoutException {

        MIDataReadMemoryInfo dataMemoryInfo = null;

        if (session.isActive()) {

            DsfServicesTracker tracker = new DsfServicesTracker(GdbUIPlugin.getBundleContext(), session.getId());

            final IGDBControl gdbControl = tracker.getService(IGDBControl.class);

            if (gdbControl == null)
                return null;

            CommandFactory factory = gdbControl.getCommandFactory();
            final ICommand<MIDataReadMemoryInfo> info_rm = factory.createMIDataReadMemory(gdbControl.getContext(),
                    offset, address, word_format, word_size, rows, cols, asChar);

            Query<org.eclipse.cdt.dsf.mi.service.command.output.MIDataReadMemoryInfo> query = new Query<org.eclipse.cdt.dsf.mi.service.command.output.MIDataReadMemoryInfo>() {
                @Override
                protected void execute(
                        final DataRequestMonitor<org.eclipse.cdt.dsf.mi.service.command.output.MIDataReadMemoryInfo> rm) {
                    gdbControl.queueCommand(info_rm,
                            new DataRequestMonitor<org.eclipse.cdt.dsf.mi.service.command.output.MIDataReadMemoryInfo>(
                                    gdbControl.getExecutor(), null) {
                                @Override
                                protected void handleCompleted() {
                                    rm.setData(getData());
                                    rm.done();
                                }
                            });
                }
            };

            ImmediateExecutor.getInstance().execute(query);

            try {
                // The Query.get() method is a synchronous call which blocks until the query
                // completes.
                dataMemoryInfo = query.get(maxWaitTimeInInMilliseconds, TimeUnit.MILLISECONDS);
                if (dataMemoryInfo.isError()) {
                    dataMemoryInfo = null;
                }

            } catch (InterruptedException exc) {
            } catch (ExecutionException exc) {
            } catch (TimeoutException e) {
                throw new TimeoutException("GDBSessionTranslator.readMemory() - failed, ErrorMessage: waiting time of " + maxWaitTimeInInMilliseconds + " ms passed");
            } finally {
                tracker.dispose();
            }
        }

        return dataMemoryInfo;
    }


}
