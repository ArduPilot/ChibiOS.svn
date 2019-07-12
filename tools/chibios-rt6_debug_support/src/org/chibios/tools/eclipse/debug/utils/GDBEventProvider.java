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

import org.eclipse.cdt.dsf.service.DsfSession;
import org.eclipse.cdt.dsf.debug.service.IRunControl.IResumedDMEvent;
import org.eclipse.cdt.dsf.debug.service.IRunControl.ISuspendedDMEvent;
import org.eclipse.cdt.dsf.service.DsfServiceEventHandler;
import org.eclipse.cdt.dsf.service.DsfSession.SessionEndedListener;
import org.eclipse.cdt.dsf.service.DsfSession.SessionStartedListener;
import org.eclipse.debug.core.DebugEvent;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.ui.DebugUITools;
import org.eclipse.debug.ui.contexts.DebugContextEvent;
import org.eclipse.debug.ui.contexts.IDebugContextListener;


public class GDBEventProvider implements IDebugContextListener {

		private DSFSessionStartedListener startedlistener;
		private DSFSessionEndedListener endedlistener;

		/**
		 * c'tor creates SessionStartedListener and SessionEndedListener
		 */
		public GDBEventProvider() {
			startedlistener = new DSFSessionStartedListener(); 
			DsfSession.addSessionStartedListener(startedlistener);
			endedlistener = new DSFSessionEndedListener();
			DsfSession.addSessionEndedListener(endedlistener);
			DebugUITools.getDebugContextManager().addDebugContextListener(this);
		}
		
		/**
		 * Dsf Session started listener, handles create events -> fires debugevent
		 * creates SessionListener for Resume and Suspend events
		 * @author Eduard Bechtold, I IA AS R&D DH AMB 2
		 */
		public class DSFSessionStartedListener implements SessionStartedListener {
			
			public DSFSessionStartedListener() {
				super();
				DsfSession[] sessions = DsfSession.getActiveSessions();
				for(int i = 0; i < sessions.length; i++){
					sessionStarted(sessions[i]);
				}
			}
			//Debug Session started
			public void sessionStarted(DsfSession session) {
				new SessionListener(session);
			}
		}
		/**
		 * Dsf Session ended listener, handles terminate events -> fires debugevent
		 * @author Eduard Bechtold, I IA AS R&D DH AMB 2
		 */
		public class DSFSessionEndedListener implements SessionEndedListener {
			//Debug Session ended
			public void sessionEnded(DsfSession session) {
				DebugEvent event = new DebugEvent(new DsfSessionDebugEvent(session), DebugEvent.TERMINATE);
				DebugPlugin.getDefault().fireDebugEventSet(new DebugEvent[]{event});
			}
		}
		/**
		 * Dsf Session Listener, handles Suspend and Resume events -> fires debugevents
		 * @author Eduard Bechtold, I IA AS R&D DH AMB 2
		 */
		public class SessionListener {
			
			private String sessionID;

			public SessionListener(DsfSession session) {
				super();
				this.sessionID = session.getId();
				session.addServiceEventListener(this, null);
			}

			public String getSessionID() {
				return sessionID;
			}
			//resume event
			@DsfServiceEventHandler 
			public void eventDispatched(final IResumedDMEvent e) {
				//DebugEvent event = new DebugEvent(new DsfSessionDebugEvent(DsfSession.getSession(sessionID)), DebugEvent.RESUME);
				//DebugPlugin.getDefault().fireDebugEventSet(new DebugEvent[]{event});
			}

			//suspend event
			@DsfServiceEventHandler 
			public void eventDispatched(final ISuspendedDMEvent e) {
				DebugEvent event = new DebugEvent(new DsfSessionDebugEvent(DsfSession.getSession(sessionID)), DebugEvent.SUSPEND);
				DebugPlugin.getDefault().fireDebugEventSet(new DebugEvent[]{event});
			}

		}
		
		public class DsfSessionDebugEvent{
			private DsfSession session;
			public DsfSessionDebugEvent(DsfSession session){
				this.session = session;
			}
			public DsfSession getSession() {
				return session;
			}
		}


	/**
	 * Closes the listener, removes DsfSession listener
	 */
	public void dispose() {
		DsfSession.removeSessionStartedListener(startedlistener);
		DsfSession.removeSessionEndedListener(endedlistener);
		DebugUITools.getDebugContextManager().removeDebugContextListener(this);
	}
	


	@Override
	public void debugContextChanged(DebugContextEvent event) {
		DebugEvent e = new DebugEvent(new DebugContextChangedDebugEvent(GDBSessionTranslator.getSession(event.getContext())), DebugEvent.CHANGE);
		DebugPlugin.getDefault().fireDebugEventSet(new DebugEvent[]{e});
		
	}
	
	public class DebugContextChangedDebugEvent{
		private Object session;
		public DebugContextChangedDebugEvent(Object session){
			this.session = session;
		}
		public Object getSession() {
			return session;
		}
	}

}
