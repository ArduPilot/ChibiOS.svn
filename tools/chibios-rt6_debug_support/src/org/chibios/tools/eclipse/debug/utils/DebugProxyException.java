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

public class DebugProxyException extends Exception {

  private static final long serialVersionUID = 6860700758297226746L;

  public DebugProxyException() {
    super("Debug Proxy Exception");
  }

  public DebugProxyException(String s) {
    super(s);
  }
}
