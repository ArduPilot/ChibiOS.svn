/********************************************************************************
 * Copyright (c) 2019 Giovanni Di Sirio.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 ********************************************************************************/

package org.chibios.tools.eclipse.debug.views;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map.Entry;
import java.util.Set;

import org.chibios.tools.eclipse.debug.utils.DebugProxyException;
import org.chibios.tools.eclipse.debug.utils.HexUtils;
import org.chibios.tools.eclipse.debug.utils.KernelObjects;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.action.ControlContribution;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.action.IMenuListener;
import org.eclipse.jface.action.IMenuManager;
import org.eclipse.jface.action.IToolBarManager;
import org.eclipse.jface.action.MenuManager;
import org.eclipse.jface.action.Separator;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CTabFolder;
import org.eclipse.swt.custom.CTabItem;
import org.eclipse.swt.custom.ScrolledComposite;
import org.eclipse.swt.events.ControlAdapter;
import org.eclipse.swt.events.ControlEvent;
import org.eclipse.swt.events.FocusAdapter;
import org.eclipse.swt.events.FocusEvent;
import org.eclipse.swt.events.PaintEvent;
import org.eclipse.swt.events.PaintListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.ToolTip;
import org.eclipse.ui.IActionBars;
import org.eclipse.ui.IWorkbenchActionConstants;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.internal.IWorkbenchThemeConstants;
import org.eclipse.ui.part.ViewPart;
import org.eclipse.ui.themes.ITheme;

import org.eclipse.wb.swt.ResourceManager;
import org.eclipse.wb.swt.SWTResourceManager;

/**
 * This sample class demonstrates how to plug-in a new workbench view. The view
 * shows data obtained from the model. The sample creates a dummy model on the
 * fly, but a real implementation would connect to the model available either in
 * this or another plug-in (e.g. the workspace). The view is connected to the
 * model using a content provider.
 * <p>
 * The view uses a label provider to define how model objects should be
 * presented in the view. Each view can present the same model objects using
 * different labels and icons, if needed. Alternatively, a single label provider
 * can be shared between views in order to ensure that objects of the same type
 * are presented in the same way everywhere.
 * <p>
 */

@SuppressWarnings("restriction")
public class ChibiView extends ViewPart {

  private static final int TRACE_KIND_RUNNING = 0;
  private static final int TRACE_KIND_READY = 1;
  private static final int TRACE_KIND_SLEEPING = 2;

  private static final int TRACE_LEFT_MARGIN = 260;
  private static final int TRACE_RIGHT_MARGIN = 32;
  private static final int TRACE_TOP_MARGIN = 48;
  private static final int TRACE_LEGEND_HEIGHT = 28;
  private static final int TRACE_MARKER_HEIGHT = 20;
  private static final int TRACE_TITLE_Y = 12;
  private static final int TRACE_LEGEND_Y = 34;
  private static final int TRACE_TIME_Y = 56;
  private static final int TRACE_ISR_GAP = 10;
  private static final int TRACE_ISR_HEIGHT = 16;
  private static final int TRACE_ISR_LINE_Y = 8;
  private static final int TRACE_ROW_HEIGHT = 34;
  private static final int TRACE_ROW_GAP = 12;
  private static final int TRACE_TRACK_RUNNING_Y = 6;
  private static final int TRACE_TRACK_READY_Y = 17;
  private static final int TRACE_TRACK_SLEEP_Y = 28;
  private static final int TRACE_AXIS_GAP = 14;
  private static final int TRACE_AXIS_HEIGHT = 42;
  private static final int TRACE_AXIS_TICKS = 8;
  private static final int TRACE_BOTTOM_MARGIN = 24;
  private static final int TRACE_MIN_GRAPH_WIDTH = 360;
  private static final long TRACE_EVENT_CLUSTER_WINDOW = 256;
  private static final long TRACE_FITTED_CONTEXT = 256;
  private static final long TRACE_FITTED_CLUSTER_GAP = 20;
  private static final long TRACE_FITTED_EDGE_GAP = 12;
  private static final int TRACE_BREAK_HALF_WIDTH = 4;
  private static final int TRACE_BREAK_HALF_HEIGHT = 4;
  private static final int TRACE_BREAK_GAP = 5;
  private static final int TRACE_BREAK_CLEARANCE = TRACE_BREAK_GAP + TRACE_BREAK_HALF_WIDTH - 1;
  private static final double[] TRACE_SCALE_PRESETS = {
      0.05d, 0.1d, 0.2d, 0.5d, 1.0d, 2.0d, 5.0d, 10.0d
  };
  private static final String[] TRACE_SCALE_LABELS = {
      "x0.25", "x0.5", "x1", "x2.5", "x5", "x10", "x25", "x50"
  };
  private static final int TRACE_DEFAULT_SCALE_INDEX = 2;
  private static final double TRACE_DEFAULT_PIXELS_PER_UNIT = 0.2d;
  private static final int TRACE_MARKER_TOOLTIP_LIMIT = 4;

  /**
   * The ID of the view as specified by the extension.
   */
  public static final String ID = "org.chibios.tools.eclipse.debug.views.ChibiView";

  private CTabFolder tabFolder;
  private CTabItem tbtmGlobal;
  private CTabItem tbtmThreads;
  private CTabItem tbtmTimers;
  private CTabItem tbtmTraceBuffer;
  private CTabItem tbtmTraceGraph;
  private CTabItem tbtmStatistics;

  private Action refreshAction;
  private ControlContribution traceZoomContribution;
  private Table globalTable;
  private Table threadsTable;
  private Table timersTable;
  private Table tbTable;
  private ScrolledComposite traceGraphScrolled;
  private Canvas traceGraphCanvas;
  private Table statisticsTable;

  private KernelObjects debugger;
  private TraceGraphModel traceGraphModel;
  private TimelineMapper traceTimelineMapper;
  private List<RenderedTraceMarker> renderedTraceMarkers = new ArrayList<RenderedTraceMarker>(32);
  private ToolTip traceMarkerToolTip;
  private RenderedTraceMarker hoveredTraceMarker;
  private String hoveredTraceMarkerText;
  private TraceMarker measurementStartMarker;
  private TraceMarker measurementEndMarker;
  private long traceWindowStart = 0;
  private long traceWindowEnd = 1;
  private double tracePixelsPerUnit = TRACE_DEFAULT_PIXELS_PER_UNIT;
  private int traceScaleIndex = TRACE_DEFAULT_SCALE_INDEX;
  private Combo traceZoomCombo;

  private ITheme theme;

  private Color traceRunningColor;
  private Color traceReadyColor;
  private Color traceSleepingColor;
  private Color traceWtSemColor;
  private Color traceWtMtxColor;
  private Color traceWtCondColor;
  private Color traceWtMsgColor;
  private Color traceWtEvtColor;
  private Color traceMarkerColor;

  private FocusAdapter focus = new FocusAdapter() {
    @Override
    public void focusLost(FocusEvent e) {
      setInactive();
    }
    @Override
    public void focusGained(FocusEvent e) {
      setActive();
    }
  };

  /**
   * The constructor.
   */
  public ChibiView() {

    theme = PlatformUI.getWorkbench().getThemeManager().getCurrentTheme();
    debugger = new KernelObjects();
  }

  private void setActive() {
    tabFolder.setSelectionBackground(
        new org.eclipse.swt.graphics.Color[] {
            theme.getColorRegistry().get(IWorkbenchThemeConstants.ACTIVE_TAB_BG_START),
            theme.getColorRegistry().get(IWorkbenchThemeConstants.ACTIVE_TAB_BG_END)
        },
        new int[] {100},
        true);
    tabFolder.setSelectionForeground(theme.getColorRegistry().get(IWorkbenchThemeConstants.ACTIVE_TAB_TEXT_COLOR));
  }

  private void setInactive() {
    tabFolder.setSelectionBackground(
        new org.eclipse.swt.graphics.Color[] {
            theme.getColorRegistry().get(IWorkbenchThemeConstants.INACTIVE_TAB_BG_START),
            theme.getColorRegistry().get(IWorkbenchThemeConstants.INACTIVE_TAB_BG_END)
        },
        new int[] {theme.getInt(IWorkbenchThemeConstants.ACTIVE_TAB_PERCENT)},
        true);
    tabFolder.setSelectionForeground(theme.getColorRegistry().get(IWorkbenchThemeConstants.INACTIVE_TAB_TEXT_COLOR));
  }

  /**
   * This is a callback that will allow us to create the viewer and initialize
   * it.
   */
  public void createPartControl(Composite parent) {

    initializeTraceGraphColors(parent.getDisplay());

    tabFolder = new CTabFolder(parent, SWT.BORDER | SWT.BOTTOM);
    tabFolder.setFont(theme.getFontRegistry().get(IWorkbenchThemeConstants.TAB_TEXT_FONT));
    tabFolder.setBackground(theme.getColorRegistry().get(IWorkbenchThemeConstants.INACTIVE_TAB_BG_END));
    tabFolder.addSelectionListener(new SelectionAdapter() {
      @Override
      public void widgetSelected(SelectionEvent e) {
        setActive();
        tabFolder.getSelection().getControl().setFocus();
      }
    });
    tabFolder.addFocusListener(new FocusAdapter() {
      @Override
      public void focusGained(FocusEvent e) {
        tabFolder.getSelection().getControl().setFocus();
      }
    });
    setInactive();
    tabFolder.setSimple(false);

    tbtmGlobal = new CTabItem(tabFolder, SWT.NONE);
    tbtmGlobal.setText("Global");

    globalTable = new Table(tabFolder, SWT.FULL_SELECTION);
    globalTable.addFocusListener(focus);
    globalTable.setFont(SWTResourceManager.getFont("Courier New", 8, SWT.NORMAL));
    tbtmGlobal.setControl(globalTable);
    globalTable.setHeaderVisible(true);

    TableColumn tblclmnGlobalHidden = new TableColumn(globalTable, SWT.RIGHT);
    tblclmnGlobalHidden.setWidth(0);
    tblclmnGlobalHidden.setText("");

    TableColumn tblclmnGlobalVariableName = new TableColumn(globalTable, SWT.LEFT);
    tblclmnGlobalVariableName.setWidth(150);
    tblclmnGlobalVariableName.setText("Variable");

    TableColumn tblclmnGlobalVariableValue = new TableColumn(globalTable, SWT.LEFT);
    tblclmnGlobalVariableValue.setWidth(300);
    tblclmnGlobalVariableValue.setText("Value");

    TableColumn tblclmnGlobalVariableFiller = new TableColumn(globalTable, SWT.FILL);
    tblclmnGlobalVariableFiller.setWidth(1);
    tblclmnGlobalVariableFiller.setText("");

    tbtmThreads = new CTabItem(tabFolder, SWT.NONE);
    tbtmThreads.setText("Threads");

    threadsTable = new Table(tabFolder, SWT.FULL_SELECTION);
    threadsTable.addFocusListener(focus);
    tbtmThreads.setControl(threadsTable);
    threadsTable.setFont(SWTResourceManager.getFont("Courier New", 8, SWT.NORMAL));
    threadsTable.setHeaderVisible(true);

    TableColumn tblclmnThreadAddress = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadAddress.setWidth(72);
    tblclmnThreadAddress.setText("Address");

    TableColumn tblclmnThreadLimit = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadLimit.setWidth(72);
    tblclmnThreadLimit.setText("StkLimit");

    TableColumn tblclmnThreadStack = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadStack.setWidth(72);
    tblclmnThreadStack.setText("Stack");

    TableColumn tblclmnThreadUsed = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadUsed.setWidth(72);
    tblclmnThreadUsed.setText("StkUnused");

    TableColumn tblclmnThreadName = new TableColumn(threadsTable, SWT.LEFT);
    tblclmnThreadName.setWidth(144);
    tblclmnThreadName.setText("Name");

    TableColumn tblclmnThreadState = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadState.setWidth(72);
    tblclmnThreadState.setText("State");

    TableColumn tblclmnThreadFlags = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadFlags.setWidth(40);
    tblclmnThreadFlags.setText("Flgs");

    TableColumn tblclmnThreadPriority = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadPriority.setWidth(40);
    tblclmnThreadPriority.setText("Prio");

    TableColumn tblclmnThreadRefs = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadRefs.setWidth(40);
    tblclmnThreadRefs.setText("Refs");

    TableColumn tblclmnThreadTime = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadTime.setWidth(64);
    tblclmnThreadTime.setText("Time");

    TableColumn tblclmnThreadShared = new TableColumn(threadsTable, SWT.LEFT);
    tblclmnThreadShared.setWidth(72);
    tblclmnThreadShared.setText("Obj/Msg");

    TableColumn tblclmnThreadContextSwitches = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadContextSwitches.setWidth(96);
    tblclmnThreadContextSwitches.setText("Switches");

    TableColumn tblclmnThreadWorstPath = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadWorstPath.setWidth(96);
    tblclmnThreadWorstPath.setText("Worst Path");

    TableColumn tblclmnThreadCumulativeTime = new TableColumn(threadsTable, SWT.RIGHT);
    tblclmnThreadCumulativeTime.setWidth(192);
    tblclmnThreadCumulativeTime.setText("Cumulative Time");

    TableColumn tblclmnThreadFiller = new TableColumn(threadsTable, SWT.FILL);
    tblclmnThreadFiller.setWidth(1);
    tblclmnThreadFiller.setText("");

    tbtmTimers = new CTabItem(tabFolder, SWT.NONE);
    tbtmTimers.setText("Timers");

    timersTable = new Table(tabFolder, SWT.FULL_SELECTION);
    timersTable.addFocusListener(focus);
    tbtmTimers.setControl(timersTable);
    timersTable.setFont(SWTResourceManager.getFont("Courier New", 8, SWT.NORMAL));
    timersTable.setHeaderVisible(true);

    TableColumn tblclmnTimerAddress = new TableColumn(timersTable, SWT.RIGHT);
    tblclmnTimerAddress.setWidth(72);
    tblclmnTimerAddress.setText("Address");

    TableColumn tblclmnTimerTime = new TableColumn(timersTable, SWT.RIGHT);
    tblclmnTimerTime.setWidth(72);
    tblclmnTimerTime.setText("Time");

    TableColumn tblclmnTimerDelta = new TableColumn(timersTable, SWT.RIGHT);
    tblclmnTimerDelta.setWidth(72);
    tblclmnTimerDelta.setText("Delta");

    TableColumn tblclmnTimerCallback = new TableColumn(timersTable, SWT.RIGHT);
    tblclmnTimerCallback.setWidth(72);
    tblclmnTimerCallback.setText("Callback");

    TableColumn tblclmnTimerParameter = new TableColumn(timersTable, SWT.LEFT);
    tblclmnTimerParameter.setWidth(72);
    tblclmnTimerParameter.setText("Param");

    TableColumn tblclmnTimerLastDeadline = new TableColumn(timersTable, SWT.RIGHT);
    tblclmnTimerLastDeadline.setWidth(100);
    tblclmnTimerLastDeadline.setText("Last Deadline");

    TableColumn tblclmnTimerReload = new TableColumn(timersTable, SWT.RIGHT);
    tblclmnTimerReload.setWidth(100);
    tblclmnTimerReload.setText("Reload");

    TableColumn tblclmnTimerFiller = new TableColumn(timersTable, SWT.FILL);
    tblclmnTimerFiller.setWidth(1);
    tblclmnTimerFiller.setText("");

    tbtmTraceBuffer = new CTabItem(tabFolder, SWT.NONE);
    tbtmTraceBuffer.setText("TraceBuffer");

    tbTable = new Table(tabFolder, SWT.FULL_SELECTION);
    tbTable.addFocusListener(focus);
    tbTable.setFont(SWTResourceManager.getFont("Courier New", 8, SWT.NORMAL));
    tbtmTraceBuffer.setControl(tbTable);
    tbTable.setHeaderVisible(true);

    TableColumn tblclmnTraceBufferHidden = new TableColumn(tbTable, SWT.RIGHT);
    tblclmnTraceBufferHidden.setWidth(0);
    tblclmnTraceBufferHidden.setText("");

    TableColumn tblclmnTraceBufferIndex = new TableColumn(tbTable, SWT.RIGHT);
    tblclmnTraceBufferIndex.setWidth(48);
    tblclmnTraceBufferIndex.setText("Event");

    TableColumn tblclmnTraceBufferType = new TableColumn(tbTable, SWT.LEFT);
    tblclmnTraceBufferType.setWidth(80);
    tblclmnTraceBufferType.setText("Type");

    TableColumn tblclmnTraceBufferTime = new TableColumn(tbTable, SWT.RIGHT);
    tblclmnTraceBufferTime.setWidth(80);
    tblclmnTraceBufferTime.setText("SysTime");

    TableColumn tblclmnTraceBufferStamp = new TableColumn(tbTable, SWT.RIGHT);
    tblclmnTraceBufferStamp.setWidth(80);
    tblclmnTraceBufferStamp.setText("RT Stamp");

    TableColumn tblclmnTraceBufferPrevAddress = new TableColumn(tbTable, SWT.RIGHT);
    tblclmnTraceBufferPrevAddress.setWidth(72);
    tblclmnTraceBufferPrevAddress.setText("From");

    TableColumn tblclmnTraceBufferPrevName = new TableColumn(tbTable, SWT.LEFT);
    tblclmnTraceBufferPrevName.setWidth(144);
    tblclmnTraceBufferPrevName.setText("Name");

    TableColumn tblclmnTraceBufferState = new TableColumn(tbTable, SWT.LEFT);
    tblclmnTraceBufferState.setWidth(72);
    tblclmnTraceBufferState.setText("State");

    TableColumn tblclmnTraceBufferShared = new TableColumn(tbTable, SWT.RIGHT);
    tblclmnTraceBufferShared.setWidth(72);
    tblclmnTraceBufferShared.setText("Obj/Msg");

    TableColumn tblclmnTraceBufferCurrentAddress = new TableColumn(tbTable, SWT.RIGHT);
    tblclmnTraceBufferCurrentAddress.setWidth(72);
    tblclmnTraceBufferCurrentAddress.setText("To");

    TableColumn tblclmnTraceBufferCurrentName = new TableColumn(tbTable, SWT.LEFT);
    tblclmnTraceBufferCurrentName.setWidth(144);
    tblclmnTraceBufferCurrentName.setText("Name");

    TableColumn tblclmnTraceBufferFiller = new TableColumn(tbTable, SWT.FILL);
    tblclmnTraceBufferFiller.setWidth(1);
    tblclmnTraceBufferFiller.setText("");

    tbtmTraceGraph = new CTabItem(tabFolder, SWT.NONE);
    tbtmTraceGraph.setText("TraceGraph");

    traceGraphScrolled = new ScrolledComposite(tabFolder, SWT.H_SCROLL | SWT.V_SCROLL | SWT.BORDER);
    traceGraphScrolled.addFocusListener(focus);
    traceGraphScrolled.setExpandHorizontal(false);
    traceGraphScrolled.setExpandVertical(false);
    tbtmTraceGraph.setControl(traceGraphScrolled);

    traceGraphCanvas = new Canvas(traceGraphScrolled, SWT.DOUBLE_BUFFERED);
    traceGraphCanvas.addFocusListener(focus);
    traceGraphCanvas.addPaintListener(new PaintListener() {
      @Override
      public void paintControl(PaintEvent e) {
        paintTraceGraph(e);
      }
    });
    traceMarkerToolTip = new ToolTip(parent.getShell(), SWT.BALLOON);
    traceGraphCanvas.addListener(SWT.MouseMove, event -> updateTraceMarkerTooltip(event.x, event.y));
    traceGraphCanvas.addListener(SWT.MouseDown, event -> handleTraceMarkerClick(event.x));
    traceGraphCanvas.addListener(SWT.MouseExit, event -> clearTraceMarkerHover());
    traceGraphScrolled.setContent(traceGraphCanvas);
    traceGraphScrolled.addControlListener(new ControlAdapter() {
      @Override
      public void controlResized(ControlEvent e) {
        updateTraceGraphCanvasSize();
      }
    });

    tbtmStatistics = new CTabItem(tabFolder, SWT.NONE);
    tbtmStatistics.setText("Statistics");

    statisticsTable = new Table(tabFolder, SWT.FULL_SELECTION);
    statisticsTable.setHeaderVisible(true);
    statisticsTable.setFont(SWTResourceManager.getFont("Courier New", 8, SWT.NORMAL));
    tbtmStatistics.setControl(statisticsTable);

    TableColumn tblclmnStatsHidden = new TableColumn(statisticsTable, SWT.RIGHT);
    tblclmnStatsHidden.setWidth(0);
    tblclmnStatsHidden.setText("");

    TableColumn tblclmnStatsMeasuredSection = new TableColumn(statisticsTable, SWT.LEFT);
    tblclmnStatsMeasuredSection.setWidth(200);
    tblclmnStatsMeasuredSection.setText("Measured Section");

    TableColumn tblclmnStatsBestCase = new TableColumn(statisticsTable, SWT.RIGHT);
    tblclmnStatsBestCase.setWidth(96);
    tblclmnStatsBestCase.setText("Best Case");

    TableColumn tblclmnStatsWorstCase = new TableColumn(statisticsTable, SWT.RIGHT);
    tblclmnStatsWorstCase.setWidth(96);
    tblclmnStatsWorstCase.setText("Worst Case");

    TableColumn tblclmnStatsIterations = new TableColumn(statisticsTable, SWT.RIGHT);
    tblclmnStatsIterations.setWidth(96);
    tblclmnStatsIterations.setText("Iterations");

    TableColumn tblclmnStatsCumulative = new TableColumn(statisticsTable, SWT.RIGHT);
    tblclmnStatsCumulative.setWidth(192);
    tblclmnStatsCumulative.setText("Cumulative Time");

    TableColumn tblclmnStatsFiller = new TableColumn(statisticsTable, SWT.FILL);
    tblclmnStatsFiller.setWidth(1);
    tblclmnStatsFiller.setText("");

    makeActions();
    hookContextMenu();
    contributeToActionBars();

    tabFolder.setSelection(tbtmGlobal);
  }

  private void hookContextMenu() {
    MenuManager menuMgr = new MenuManager("#PopupMenu");
    menuMgr.setRemoveAllWhenShown(true);
    menuMgr.addMenuListener(new IMenuListener() {
      public void menuAboutToShow(IMenuManager manager) {
        ChibiView.this.fillContextMenu(manager);
      }
    });
  }

  private void contributeToActionBars() {
    IActionBars bars = getViewSite().getActionBars();
    fillLocalPullDown(bars.getMenuManager());
    fillLocalToolBar(bars.getToolBarManager());
  }

  private void fillLocalPullDown(IMenuManager manager) {
    manager.add(refreshAction);
/*    manager.add(new Separator());
    manager.add(refreshAction);*/
  }

  private void fillContextMenu(IMenuManager manager) {
    manager.add(refreshAction);
    // Other plug-ins can contribute there actions here
    manager.add(new Separator(IWorkbenchActionConstants.MB_ADDITIONS));
  }

  private void fillLocalToolBar(IToolBarManager manager) {
    manager.add(refreshAction);
    manager.add(new Separator());
    manager.add(traceZoomContribution);
  }

  private void fillGlobalTable() {
    LinkedHashMap<String, String> lhm;

    // If the debugger is not yet present then do nothing.
    if (debugger == null)
      return;

    // Reading the list of global variables, null can be returned if the debugger
    // does not respond.
    try {
      lhm = debugger.readGlobalVariables();
      if (lhm == null)
        return;
    } catch (DebugProxyException e) {
      showMessage("Error: " + e.getMessage() + ".");
      return;
    }

    globalTable.removeAll();

    Set<Entry<String, String>> set = lhm.entrySet();
    for (Entry<String, String> entry : set) {
      TableItem tableItem = new TableItem(globalTable, SWT.NONE);
      tableItem.setText(new String[] {
        "",
        entry.getKey(),
        entry.getValue()
      });
    }
  }

  private String makeHex(String s) {
    try {
      s = HexUtils.dword2HexString((int)HexUtils.parseNumber(s));
    } catch (Exception e) {}
    return s;
  }

  private void fillThreadsTable() {
    LinkedHashMap<String, HashMap<String, String>> lhm;

    // If the debugger is not yet present then do nothing.
    if (debugger == null)
      return;

    // Reading the list of threads, null can be returned if the debugger
    // does not respond.
    try {
      lhm = debugger.readThreads();
      if (lhm == null)
        return;
    } catch (DebugProxyException e) {
      showMessage("Error: " + e.getMessage() + ".");
      return;
    }

    threadsTable.removeAll();

    Set<Entry<String, HashMap<String, String>>> set = lhm.entrySet();
    for (Entry<String, HashMap<String, String>> entry : set) {
      HashMap<String, String> map = entry.getValue();
      TableItem tableItem = new TableItem(threadsTable, SWT.NONE);
      tableItem.setText(new String[] {
        makeHex(entry.getKey()),
        makeHex(map.get("stklimit")),
        makeHex(map.get("stack")),
        map.get("stkunused"),
        map.get("name"),
        map.get("state_s"),
        HexUtils.byte2HexString((int)HexUtils.parseNumber(map.get("flags"))),
        map.get("prio"),
        map.get("refs"),
        map.get("time"),
        makeHex(map.get("wtobjp")),
        map.get("stats_n"),
        map.get("stats_worst"),
        map.get("stats_cumulative")
      });
    }
  }

  private void fillTimersTable() {
    LinkedHashMap<String, HashMap<String, String>> lhm;

    // If the debugger is not yet present then do nothing.
    if (debugger == null)
      return;

    // Reading the list of threads, null can be returned if the debugger
    // does not respond.
    try {
      lhm = debugger.readTimers();
      if (lhm == null)
        return;
    } catch (DebugProxyException e) {
      showMessage("Error: " + e.getMessage() + ".");
      return;
    }

    timersTable.removeAll();

    Set<Entry<String, HashMap<String, String>>> set = lhm.entrySet();
    long time = 0;
    for (Entry<String, HashMap<String, String>> entry : set) {
      HashMap<String, String> map = entry.getValue();
      time = time + HexUtils.parseNumber(map.get("delta"));
      TableItem tableItem = new TableItem(timersTable, SWT.NONE);
      tableItem.setText(new String[] {
        makeHex(entry.getKey()),
        Long.toString(time),
        "+" + HexUtils.parseNumber(map.get("delta")),
        makeHex(map.get("func")),
        makeHex(map.get("par")),
        map.get("last"),
        map.get("reload")
      });
    }
  }

  private void fillTraceBufferTable() {
    LinkedHashMap<String, HashMap<String, String>> lhm, lhmthreads;

    // If the debugger is not yet present then do nothing.
    if (debugger == null)
      return;

    // Read active threads for retrieving names.
    try {
      lhmthreads = debugger.readThreads();
      if (lhmthreads == null)
        return;
    } catch (DebugProxyException e) {
      lhmthreads = new LinkedHashMap<String, HashMap<String, String>>(0);
    }

    // Reading the list of threads, null can be returned if the debugger
    // does not respond.
    try {
      lhm = debugger.readTraceBuffer();
      if (lhm == null)
        return;
    } catch (DebugProxyException e) {
      showMessage("Error: " + e.getMessage() + ".");
      return;
    }

    tbTable.removeAll();

    Set<Entry<String, HashMap<String, String>>> set = lhm.entrySet();
    String prev = "";
    String prevname = "";
    for (Entry<String, HashMap<String, String>> entry : set) {
      HashMap<String, String> map = entry.getValue();
      TableItem tableItem = new TableItem(tbTable, SWT.NONE);

      // Fixed fields.
      int typen = (int)HexUtils.parseNumber(map.get("type"));
      String state = map.get("state_s");
      String rtstamp = map.get("rtstamp");
      String time = map.get("time");

      // Fields depending on type.
      String[] line;
      switch (typen) {
      case 1:
        // Searches the current thread into the threads map.
        {
          String tpaddr = map.get("sw_tp");
          HashMap<String, String> thread = lhmthreads.get(tpaddr);
          String name;
          if (thread != null)
            name = thread.get("name");
          else
            name = "";
          String tp = makeHex(tpaddr);
          String msg = makeHex(map.get("sw_msg"));

          line = new String[] {
            "",
            entry.getKey(),
            "Ready",
            time,
            rtstamp,
            tp,
            name,
            "",
            msg,
            "",
            ""
          };
        }
        break;
      case 2:
        // Searches the current thread into the threads map.
        {
          String currentaddr = map.get("sw_ntp");
          HashMap<String, String> thread = lhmthreads.get(currentaddr);
          String currentname;
          if (thread != null)
            currentname = thread.get("name");
          else
            currentname = "";
          String currentThread = makeHex(currentaddr);
          String wtobjp = makeHex(map.get("sw_wtobjp"));

          line = new String[] {
            "",
            entry.getKey(),
            "Switch",
            time,
            rtstamp,
            prev,
            prevname,
            state,
            wtobjp,
            currentThread,
            currentname
          };
          prev = currentThread;
          prevname = currentname;
        }
        break;
      case 3:
        line = new String[] {
          "",
          entry.getKey(),
          "ISR-enter",
          time,
          rtstamp,
          "",
          map.get("isr_name_s"),
          "",
          "",
          "",
          ""
        };
        break;
      case 4:
        line = new String[] {
          "",
          entry.getKey(),
          "ISR-leave",
          time,
          rtstamp,
          "",
          map.get("isr_name_s"),
          "",
          "",
          "",
          ""
        };
        break;
      case 5:
        line = new String[] {
          "",
          entry.getKey(),
          "Halt",
          time,
          rtstamp,
          "",
          map.get("halt_reason_s"),
          "",
          "",
          "",
          ""
        };
        break;
      case 6:
        line = new String[] {
          "",
          entry.getKey(),
          "User",
          time,
          rtstamp,
          makeHex(map.get("user_up1")),
          "",
          "",
          "",
          makeHex(map.get("user_up2")),
          ""
        };
        break;
      default:
        line = new String[] {
          "",
          entry.getKey(),
          "Unknown",
          time,
          rtstamp,
          "",
          "",
          "",
          "",
          "",
          ""
        };
      }

      tableItem.setText(line);
    }
  }

  private void fillTraceGraph() {
    LinkedHashMap<String, HashMap<String, String>> lhm, lhmthreads;

    if (debugger == null)
      return;

    try {
      lhmthreads = debugger.readThreads();
      if (lhmthreads == null)
        return;
    } catch (DebugProxyException e) {
      lhmthreads = new LinkedHashMap<String, HashMap<String, String>>(0);
    }

    try {
      lhm = debugger.readTraceBuffer();
      if (lhm == null)
        return;
    } catch (DebugProxyException e) {
      showMessage("Error: " + e.getMessage() + ".");
      return;
    }

    traceGraphModel = buildTraceGraphModel(lhmthreads, lhm);
    measurementStartMarker = null;
    measurementEndMarker = null;
    clearTraceMarkerHover();
    resetTraceWindow();
    rebuildTraceTimeline();
    updateTraceGraphCanvasSize();
    traceGraphCanvas.redraw();
  }

  private void fillStatisticsTable() {
    LinkedHashMap<String, HashMap<String, String>> lhm;

    // If the debugger is not yet present then do nothing.
    if (debugger == null)
      return;

    // Reading the list of global variables, null can be returned if the debugger
    // does not respond.
    try {
      lhm = debugger.readStatistics();
      if (lhm == null)
        return;
    } catch (DebugProxyException e) {
      showMessage("Error: " + e.getMessage() + ".");
      return;
    }

    statisticsTable.removeAll();

    Set<Entry<String, HashMap<String, String>>> set = lhm.entrySet();
    for (Entry<String, HashMap<String, String>> entry : set) {
      TableItem tableItem = new TableItem(statisticsTable, SWT.NONE);
      tableItem.setText(new String[] {
        "",
        entry.getKey(),
        entry.getValue().get("best"),
        entry.getValue().get("worst"),
        entry.getValue().get("n"),
        entry.getValue().get("cumulative")
      });
    }
  }

  private void makeActions() {

    // Refresh action.
    refreshAction = new Action() {
      @Override
      public void run() {
        CTabItem tabitem = tabFolder.getSelection();
        if (tabitem == null)
          return;
        if (tabitem == tbtmGlobal)
          fillGlobalTable();
        else if (tabitem == tbtmThreads)
          fillThreadsTable();
        else if (tabitem == tbtmTimers)
          fillTimersTable();
        else if (tabitem == tbtmTraceBuffer)
          fillTraceBufferTable();
        else if (tabitem == tbtmTraceGraph) {
          fillTraceGraph();
          if (traceGraphScrolled != null)
            traceGraphScrolled.layout(true, true);
          if (traceGraphCanvas != null) {
            updateTraceGraphCanvasSize();
            traceGraphCanvas.redraw();
          }
        }
        else if (tabitem == tbtmStatistics)
          fillStatisticsTable();
      }
    };
    refreshAction.setDisabledImageDescriptor(ResourceManager.getPluginImageDescriptor("org.eclipse.cdt.ui", "/icons/dlcl16/refresh_nav.gif"));
    refreshAction.setImageDescriptor(ResourceManager.getPluginImageDescriptor("org.eclipse.cdt.ui", "/icons/elcl16/refresh_nav.gif"));
    refreshAction.setText("Refresh");
    refreshAction.setToolTipText("Refresh current view");

    traceZoomContribution = new ControlContribution("traceZoom") {
      @Override
      protected Control createControl(Composite parent) {
        traceZoomCombo = new Combo(parent, SWT.DROP_DOWN | SWT.READ_ONLY);
        traceZoomCombo.setToolTipText("Trace zoom");
        traceZoomCombo.setItems(TRACE_SCALE_LABELS);
        traceZoomCombo.select(traceScaleIndex);
        traceZoomCombo.addSelectionListener(new SelectionAdapter() {
          @Override
          public void widgetSelected(SelectionEvent e) {
            int index = traceZoomCombo.getSelectionIndex();

            if (index >= 0)
              applyTraceScalePreset(index);
          }
        });
        return traceZoomCombo;
      }
    };

  }

  private void applyTraceScalePreset(int index) {

    if ((index < 0) || (index >= TRACE_SCALE_PRESETS.length))
      return;
    if (index == traceScaleIndex)
      return;

    applyTraceScale(TRACE_SCALE_PRESETS[index], index);
  }

  private void applyTraceScale(double newPixelsPerUnit, int newIndex) {

    double oldPixelsPerUnit = tracePixelsPerUnit;
    double centerDisplay = 0.0d;
    int clientWidth = 0;
    int originY = 0;

    if (traceGraphScrolled != null) {
      Point origin = traceGraphScrolled.getOrigin();

      clientWidth = traceGraphScrolled.getClientArea().width;
      originY = origin.y;
      if (oldPixelsPerUnit > 0.0d)
        centerDisplay = Math.max(0.0d,
                                 ((origin.x + (clientWidth / 2.0d)) - TRACE_LEFT_MARGIN) /
                                 oldPixelsPerUnit);
    }

    tracePixelsPerUnit = newPixelsPerUnit;
    traceScaleIndex = newIndex;
    updateTraceZoomSelection();
    updateTraceGraphCanvasSize();

    if ((traceGraphScrolled != null) && (traceGraphCanvas != null) && !traceGraphCanvas.isDisposed()) {
      int contentWidth = traceGraphCanvas.getSize().x;
      int maxOriginX = Math.max(0, contentWidth - clientWidth);
      int newCenterX = TRACE_LEFT_MARGIN + (int)Math.round(centerDisplay * newPixelsPerUnit);
      int newOriginX = Math.max(0, Math.min(maxOriginX, newCenterX - (clientWidth / 2)));

      traceGraphScrolled.setOrigin(newOriginX, originY);
    }

    if ((traceGraphCanvas != null) && !traceGraphCanvas.isDisposed())
      traceGraphCanvas.redraw();
  }

  private void updateTraceZoomSelection() {

    if ((traceZoomCombo != null) && !traceZoomCombo.isDisposed() &&
        (traceZoomCombo.getSelectionIndex() != traceScaleIndex))
      traceZoomCombo.select(traceScaleIndex);
  }

  private void showMessage(String message) {
    MessageDialog.openInformation(tabFolder.getShell(),
        "ChibiOS/RT Views", message);
  }

  private void initializeTraceGraphColors(Display display) {

    traceRunningColor = new Color(display, 46, 125, 50);
    traceReadyColor = new Color(display, 25, 118, 210);
    traceSleepingColor = new Color(display, 117, 117, 117);
    traceWtSemColor = new Color(display, 251, 192, 45);
    traceWtMtxColor = new Color(display, 239, 108, 0);
    traceWtCondColor = new Color(display, 142, 36, 170);
    traceWtMsgColor = new Color(display, 0, 137, 123);
    traceWtEvtColor = new Color(display, 94, 53, 177);
    traceMarkerColor = new Color(display, 198, 40, 40);
  }

  private void updateTraceGraphCanvasSize() {

    if ((traceGraphCanvas == null) || traceGraphCanvas.isDisposed())
      return;

    int width = TRACE_LEFT_MARGIN + TRACE_RIGHT_MARGIN + 1;
    int height = TRACE_TOP_MARGIN + TRACE_LEGEND_HEIGHT + TRACE_MARKER_HEIGHT +
                 TRACE_ISR_GAP + TRACE_AXIS_HEIGHT + TRACE_BOTTOM_MARGIN;

    if (traceTimelineMapper != null) {
      width = TRACE_LEFT_MARGIN +
              Math.max(TRACE_MIN_GRAPH_WIDTH,
                       (int)Math.ceil(traceTimelineMapper.displaySpan * tracePixelsPerUnit)) +
              TRACE_RIGHT_MARGIN;
    }

    if (traceGraphModel != null) {
      height = TRACE_TOP_MARGIN +
               TRACE_LEGEND_HEIGHT +
               TRACE_MARKER_HEIGHT +
               (traceGraphModel.isrLanes.size() * (TRACE_ISR_HEIGHT + TRACE_ISR_GAP)) +
               (traceGraphModel.lanes.size() * (TRACE_ROW_HEIGHT + TRACE_ROW_GAP)) +
               TRACE_AXIS_GAP +
               TRACE_AXIS_HEIGHT +
               TRACE_BOTTOM_MARGIN;
    }

    if (traceGraphScrolled != null) {
      int clientHeight = traceGraphScrolled.getClientArea().height;

      if (clientHeight > height)
        height = clientHeight;
    }

    traceGraphCanvas.setSize(width, height);
    if (traceGraphScrolled != null)
      traceGraphScrolled.setMinSize(width, height);
  }

  private TraceGraphModel buildTraceGraphModel(
      LinkedHashMap<String, HashMap<String, String>> lhmthreads,
      LinkedHashMap<String, HashMap<String, String>> lhmtrace) {

    LinkedHashMap<String, TraceLane> lanes = new LinkedHashMap<String, TraceLane>(32);
    LinkedHashMap<String, IsrLane> isrLanes = new LinkedHashMap<String, IsrLane>(16);
    HashMap<String, Integer> isrDepths = new HashMap<String, Integer>(16);
    HashMap<String, Long> isrStarts = new HashMap<String, Long>(16);
    TraceGraphModel model = new TraceGraphModel();
    String current = null;
    long rtStampCarry = 0;
    long previousRawRtStamp = -1;

    for (Entry<String, HashMap<String, String>> entry : lhmthreads.entrySet()) {
      String address = entry.getKey();
      HashMap<String, String> thread = entry.getValue();
      TraceLane lane = new TraceLane();
      lane.address = address;
      lane.name = thread.get("name");
      lanes.put(address, lane);
    }

    for (Entry<String, HashMap<String, String>> entry : lhmtrace.entrySet()) {
      HashMap<String, String> map = entry.getValue();
      int eventIndex = Integer.parseInt(entry.getKey());
      long rawRtStamp = HexUtils.parseNumber(map.get("rtstamp"));
      long time;
      int typen = (int)HexUtils.parseNumber(map.get("type"));

      if ((previousRawRtStamp >= 0) && (rawRtStamp < previousRawRtStamp))
        rtStampCarry += (1L << 24);
      previousRawRtStamp = rawRtStamp;
      time = rtStampCarry + rawRtStamp;

      if (!model.hasEvents) {
        model.minTime = time;
        model.maxTime = time;
        model.hasEvents = true;
      }
      else {
        if (time < model.minTime)
          model.minTime = time;
        if (time > model.maxTime)
          model.maxTime = time;
      }

      if (typen == 1) {
        String address = map.get("sw_tp");
        TraceLane lane = ensureTraceLane(lanes, lhmthreads, address);
        TraceMarker marker = new TraceMarker();

        marker.eventIndex = eventIndex;
        marker.time = time;
        marker.sysTime = Long.parseLong(map.get("time"));
        marker.label = "Ready";
        marker.details = makeReadyMarkerDetails(entry.getKey(), map, lane);
        model.markers.add(marker);

        markLaneSeen(lane, time);
        setLaneState(lane, time, TRACE_KIND_READY, "READY");
      }
      else if (typen == 2) {
        String state = safeTraceState(map.get("state_s"));
        String next = map.get("sw_ntp");
        TraceLane fromLane = null;
        TraceLane lane;
        TraceMarker marker = new TraceMarker();

        if (current != null) {
          fromLane = ensureTraceLane(lanes, lhmthreads, current);

          markLaneSeen(fromLane, time);
          if ("FINAL".equals(state))
            terminateLane(fromLane, time);
          else
            setLaneState(fromLane, time, classifyTraceState(state), state);
        }

        lane = ensureTraceLane(lanes, lhmthreads, next);
        marker.eventIndex = eventIndex;
        marker.time = time;
        marker.sysTime = Long.parseLong(map.get("time"));
        marker.label = "Switch";
        marker.details = makeSwitchMarkerDetails(entry.getKey(), map, fromLane, lane);
        model.markers.add(marker);

        markLaneSeen(lane, time);
        setLaneState(lane, time, TRACE_KIND_RUNNING, "CURRENT");
        current = next;
      }
      else if (typen == 3) {
        String isrName = safeIsrName(map.get("isr_name_s"));
        TraceMarker marker = new TraceMarker();
        marker.eventIndex = eventIndex;
        marker.time = time;
        marker.sysTime = Long.parseLong(map.get("time"));
        marker.label = "ISR " + isrName;
        marker.details = makeTraceMarkerDetails(entry.getKey(), map, "ISR-enter", isrName);
        model.markers.add(marker);

        ensureIsrLane(isrLanes, isrName);

        Integer depth = isrDepths.get(isrName);
        if (depth == null)
          depth = Integer.valueOf(0);
        if (depth.intValue() == 0)
          isrStarts.put(isrName, Long.valueOf(time));
        isrDepths.put(isrName, Integer.valueOf(depth.intValue() + 1));
      }
      else if (typen == 4) {
        String isrName = safeIsrName(map.get("isr_name_s"));
        TraceMarker marker = new TraceMarker();
        marker.eventIndex = eventIndex;
        marker.time = time;
        marker.sysTime = Long.parseLong(map.get("time"));
        marker.label = "ISR end " + isrName;
        marker.details = makeTraceMarkerDetails(entry.getKey(), map, "ISR-leave", isrName);
        model.markers.add(marker);

        ensureIsrLane(isrLanes, isrName);

        Integer depth = isrDepths.get(isrName);
        if ((depth != null) && (depth.intValue() > 0)) {
          int newDepth = depth.intValue() - 1;
          if (newDepth == 0) {
            Long start = isrStarts.get(isrName);
            TraceSegment segment = new TraceSegment();
            if (start != null)
              segment.startTime = start.longValue();
            else
              segment.startTime = time;
            segment.endTime = time;
            segment.kind = TRACE_KIND_RUNNING;
            segment.state = isrName;
            isrLanes.get(isrName).segments.add(segment);
            isrStarts.remove(isrName);
            isrDepths.remove(isrName);
          }
          else {
            isrDepths.put(isrName, Integer.valueOf(newDepth));
          }
        }
      }
    }

    if (!model.hasEvents) {
      model.minTime = 0;
      model.maxTime = 1;
    }
    else if (model.maxTime == model.minTime)
      model.maxTime = model.minTime + 1;

    for (Entry<String, Integer> entry : isrDepths.entrySet()) {
      if (entry.getValue().intValue() > 0) {
        String isrName = entry.getKey();
        Long start = isrStarts.get(isrName);
        TraceSegment segment = new TraceSegment();
        if (start != null)
          segment.startTime = start.longValue();
        else
          segment.startTime = model.minTime;
        segment.endTime = model.maxTime;
        segment.kind = TRACE_KIND_RUNNING;
        segment.state = isrName;
        ensureIsrLane(isrLanes, isrName).segments.add(segment);
      }
    }

    model.isrLanes.addAll(isrLanes.values());
    for (TraceLane lane : lanes.values()) {
      if (lane.segment != null)
        lane.segment.endTime = model.maxTime;
      model.lanes.add(lane);
    }
    return model;
  }

  private void resetTraceWindow() {

    if (traceGraphModel == null) {
      traceWindowStart = 0;
      traceWindowEnd = 1;
      return;
    }

    traceWindowStart = traceGraphModel.minTime;
    traceWindowEnd = Math.max(traceWindowStart + 1, traceGraphModel.maxTime);
  }

  private void rebuildTraceTimeline() {

    if (traceGraphModel == null) {
      traceTimelineMapper = null;
      return;
    }

    if (traceWindowStart < traceGraphModel.minTime)
      traceWindowStart = traceGraphModel.minTime;
    if (traceWindowEnd > traceGraphModel.maxTime)
      traceWindowEnd = traceGraphModel.maxTime;
    if (traceWindowEnd <= traceWindowStart)
      traceWindowEnd = traceWindowStart + 1;

    traceTimelineMapper = buildTimelineMapper(traceGraphModel,
                                              traceWindowStart,
                                              traceWindowEnd);
  }

  private TimelineMapper buildTimelineMapper(TraceGraphModel model,
                                             long windowStart,
                                             long windowEnd) {

    TimelineMapper mapper = new TimelineMapper();
    long displayCursor = 0;
    mapper.windowStart = windowStart;
    mapper.windowEnd = windowEnd;

    List<TimeCluster> clusters = collectTimeClusters(model, windowStart, windowEnd);

    if (clusters.isEmpty()) {
      TimelineSpan span = new TimelineSpan();
      span.rawStart = windowStart;
      span.rawEnd = windowEnd;
      span.displayStart = 0;
      span.displayEnd = Math.max(1, windowEnd - windowStart);
      span.displayRawStart = span.displayStart;
      span.displayRawEnd = span.displayEnd;
      span.condensedGap = false;
      mapper.spans.add(span);
      mapper.displaySpan = Math.max(1, span.displayEnd);
      populateAxisTicks(mapper);
      return mapper;
    }

    if (windowStart < clusters.get(0).startTime) {
      TimelineSpan span = new TimelineSpan();
      span.rawStart = windowStart;
      span.rawEnd = clusters.get(0).startTime;
      span.displayStart = displayCursor;
      span.displayEnd = displayCursor + TRACE_FITTED_EDGE_GAP;
      span.displayRawStart = span.displayStart;
      span.displayRawEnd = span.displayEnd;
      span.condensedGap = true;
      mapper.spans.add(span);
      displayCursor = span.displayEnd;
    }

    for (int i = 0; i < clusters.size(); i++) {
      TimeCluster cluster = clusters.get(i);
      long visibleStart = getFittedClusterStart(clusters, i, windowStart);
      long visibleEnd = getFittedClusterEnd(clusters, i, windowEnd);
      TimelineSpan span = new TimelineSpan();

      span.rawStart = visibleStart;
      span.rawEnd = Math.max(visibleStart + 1, visibleEnd);
      span.displayStart = displayCursor;
      span.displayEnd = displayCursor + Math.max(1, span.rawEnd - span.rawStart);
      span.displayRawStart = span.displayStart;
      span.displayRawEnd = span.displayEnd;
      span.condensedGap = false;
      mapper.spans.add(span);
      displayCursor = span.displayEnd;

      if (i < (clusters.size() - 1)) {
        long nextVisibleStart = getFittedClusterStart(clusters, i + 1, windowStart);
        if (span.rawEnd < nextVisibleStart) {
          TimelineSpan gap = new TimelineSpan();
          gap.rawStart = span.rawEnd;
          gap.rawEnd = nextVisibleStart;
          gap.displayStart = displayCursor;
          gap.displayEnd = displayCursor + TRACE_FITTED_CLUSTER_GAP;
          gap.displayRawStart = gap.displayStart;
          gap.displayRawEnd = gap.displayEnd;
          gap.condensedGap = true;
          mapper.spans.add(gap);
          displayCursor = gap.displayEnd;
        }
      }
    }

    if (clusters.get(clusters.size() - 1).endTime < windowEnd) {
      TimelineSpan span = new TimelineSpan();
      span.rawStart = clusters.get(clusters.size() - 1).endTime;
      span.rawEnd = windowEnd;
      span.displayStart = displayCursor;
      span.displayEnd = displayCursor + TRACE_FITTED_EDGE_GAP;
      span.displayRawStart = span.displayStart;
      span.displayRawEnd = span.displayEnd;
      span.condensedGap = true;
      mapper.spans.add(span);
      displayCursor = span.displayEnd;
    }

    mapper.displaySpan = Math.max(1, displayCursor);
    populateAxisTicks(mapper);

    return mapper;
  }

  private List<TimeCluster> collectTimeClusters(TraceGraphModel model,
                                                long windowStart,
                                                long windowEnd) {

    ArrayList<Long> times = new ArrayList<Long>(64);

    for (IsrLane lane : model.isrLanes) {
      for (TraceSegment segment : lane.segments) {
        collectSegmentBoundary(times, segment.startTime, windowStart, windowEnd);
        collectSegmentBoundary(times, segment.endTime, windowStart, windowEnd);
      }
    }

    for (TraceLane lane : model.lanes) {
      for (TraceSegment segment : lane.segments) {
        collectSegmentBoundary(times, segment.startTime, windowStart, windowEnd);
        collectSegmentBoundary(times, segment.endTime, windowStart, windowEnd);
      }
    }

    Collections.sort(times);

    ArrayList<Long> unique = new ArrayList<Long>(times.size());
    Long previous = null;
    for (Long time : times) {
      if ((previous == null) || (previous.longValue() != time.longValue())) {
        unique.add(time);
        previous = time;
      }
    }

    if (unique.isEmpty())
      return new ArrayList<TimeCluster>(0);

    ArrayList<TimeCluster> clustered = new ArrayList<TimeCluster>(unique.size());
    long clusterStart = unique.get(0).longValue();
    long clusterEnd = clusterStart;

    for (int i = 1; i < unique.size(); i++) {
      long time = unique.get(i).longValue();

      if ((time - clusterEnd) <= TRACE_EVENT_CLUSTER_WINDOW) {
        clusterEnd = time;
      }
      else {
        clustered.add(new TimeCluster(clusterStart, Math.max(clusterStart + 1, clusterEnd)));
        clusterStart = time;
        clusterEnd = time;
      }
    }

    clustered.add(new TimeCluster(clusterStart, Math.max(clusterStart + 1, clusterEnd)));

    return clustered;
  }

  private String makeTraceMarkerDetails(String eventIndex,
                                        HashMap<String, String> map,
                                        String type,
                                        String subject) {

    StringBuilder sb = new StringBuilder(96);

    sb.append("Event ").append(eventIndex);
    sb.append('\n').append("Type: ").append(type);
    sb.append('\n').append("SysTime: ").append(map.get("time"));
    sb.append('\n').append("RT Stamp: ").append(map.get("rtstamp"));
    if ((subject != null) && (subject.length() > 0))
      sb.append('\n').append("Name: ").append(subject);

    return sb.toString();
  }

  private String makeReadyMarkerDetails(String eventIndex,
                                        HashMap<String, String> map,
                                        TraceLane lane) {

    StringBuilder sb = new StringBuilder(128);

    sb.append("Event ").append(eventIndex);
    sb.append('\n').append("Type: Ready");
    sb.append('\n').append("SysTime: ").append(map.get("time"));
    sb.append('\n').append("RT Stamp: ").append(map.get("rtstamp"));
    sb.append('\n').append("Thread: ").append(makeTraceLaneLabel(lane));
    sb.append('\n').append("Msg: ").append(makeHex(map.get("sw_msg")));

    return sb.toString();
  }

  private String makeSwitchMarkerDetails(String eventIndex,
                                         HashMap<String, String> map,
                                         TraceLane fromLane,
                                         TraceLane toLane) {

    StringBuilder sb = new StringBuilder(160);

    sb.append("Event ").append(eventIndex);
    sb.append('\n').append("Type: Switch");
    sb.append('\n').append("SysTime: ").append(map.get("time"));
    sb.append('\n').append("RT Stamp: ").append(map.get("rtstamp"));
    if (fromLane != null)
      sb.append('\n').append("From: ").append(makeTraceLaneLabel(fromLane));
    if (toLane != null)
      sb.append('\n').append("To: ").append(makeTraceLaneLabel(toLane));
    sb.append('\n').append("State: ").append(safeTraceState(map.get("state_s")));
    sb.append('\n').append("Obj/Msg: ").append(makeHex(map.get("sw_wtobjp")));

    return sb.toString();
  }

  private long getFittedClusterStart(List<TimeCluster> clusters, int index, long windowStart) {

    TimeCluster cluster = clusters.get(index);
    long start = Math.max(windowStart, cluster.startTime - TRACE_FITTED_CONTEXT);

    if (index > 0) {
      TimeCluster previous = clusters.get(index - 1);
      long boundary = (previous.endTime + cluster.startTime) / 2;
      if (start < boundary)
        start = boundary;
    }

    return start;
  }

  private long getFittedClusterEnd(List<TimeCluster> clusters, int index, long windowEnd) {

    TimeCluster cluster = clusters.get(index);
    long end = Math.min(windowEnd, cluster.endTime + TRACE_FITTED_CONTEXT);

    if (index < (clusters.size() - 1)) {
      TimeCluster next = clusters.get(index + 1);
      long boundary = (cluster.endTime + next.startTime) / 2;
      if (end > boundary)
        end = boundary;
    }

    return Math.max(cluster.startTime + 1, end);
  }

  private void collectSegmentBoundary(List<Long> times,
                                      long time,
                                      long windowStart,
                                      long windowEnd) {

    if ((time >= windowStart) && (time <= windowEnd))
      times.add(Long.valueOf(time));
  }

  private TraceLane ensureTraceLane(
      LinkedHashMap<String, TraceLane> lanes,
      LinkedHashMap<String, HashMap<String, String>> lhmthreads,
      String address) {

    TraceLane lane = lanes.get(address);

    if (lane == null) {
      lane = new TraceLane();
      lane.address = address;

      HashMap<String, String> thread = lhmthreads.get(address);
      if (thread != null)
        lane.name = thread.get("name");
      lanes.put(address, lane);
    }

    return lane;
  }

  private IsrLane ensureIsrLane(LinkedHashMap<String, IsrLane> lanes, String name) {

    IsrLane lane = lanes.get(name);

    if (lane == null) {
      lane = new IsrLane();
      lane.name = name;
      lanes.put(name, lane);
    }

    return lane;
  }

  private String safeIsrName(String name) {

    if ((name == null) || (name.length() == 0))
      return "<unnamed>";

    return name;
  }

  private String safeTraceState(String state) {

    if (state == null)
      return "";

    return state;
  }

  private void markLaneSeen(TraceLane lane, long time) {

    if (lane.firstSeen == Long.MAX_VALUE)
      lane.firstSeen = time;
  }

  private int classifyTraceState(String state) {

    if ("READY".equals(state))
      return TRACE_KIND_READY;

    return TRACE_KIND_SLEEPING;
  }

  private void setLaneState(TraceLane lane, long time, int kind, String state) {

    String stateValue = safeTraceState(state);

    if ((lane.segment != null) &&
        (lane.segment.kind == kind) &&
        lane.segment.state.equals(stateValue)) {
      lane.segment.endTime = time;
      lane.terminated = false;
      return;
    }

    if (lane.segment != null)
      lane.segment.endTime = time;

    lane.terminated = false;
    lane.terminateTime = Long.MAX_VALUE;
    lane.segment = new TraceSegment();
    lane.segment.startTime = time;
    lane.segment.endTime = time;
    lane.segment.kind = kind;
    lane.segment.state = stateValue;
    lane.segments.add(lane.segment);
  }

  private void terminateLane(TraceLane lane, long time) {

    if (lane.segment != null)
      lane.segment.endTime = time;
    lane.segment = null;
    lane.terminated = true;
    lane.terminateTime = time;
  }

  private void paintTraceGraph(PaintEvent e) {

    GC gc = e.gc;
    int width = traceGraphCanvas.getSize().x;
    int graphLeft = TRACE_LEFT_MARGIN;
    int graphRight = Math.max(graphLeft + 1, width - TRACE_RIGHT_MARGIN);

    gc.setBackground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_BACKGROUND));
    gc.fillRectangle(0, 0, width, traceGraphCanvas.getSize().y);
    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_FOREGROUND));

    gc.drawText("Trace buffer timeline", 12, TRACE_TITLE_Y, true);

    if ((traceGraphModel == null) || !traceGraphModel.hasEvents) {
      gc.drawText("Refresh this tab while the target is halted to load the current trace buffer.",
                  12,
                  TRACE_TIME_Y,
                  true);
      return;
    }

    int isrTop = TRACE_TOP_MARGIN + TRACE_LEGEND_HEIGHT + TRACE_MARKER_HEIGHT + TRACE_ISR_GAP;
    int graphTop = isrTop + (traceGraphModel.isrLanes.size() * (TRACE_ISR_HEIGHT + TRACE_ISR_GAP));

    drawTraceLegend(gc, 12, TRACE_LEGEND_Y);
    gc.drawText("RT Stamp " + traceWindowStart + " .. " + traceWindowEnd +
                "  [condensed]" +
                getMeasurementSummary(),
                graphLeft,
                TRACE_TIME_Y,
                true);

    int lanesBottom = graphTop +
                      (traceGraphModel.lanes.size() * (TRACE_ROW_HEIGHT + TRACE_ROW_GAP));
    int axisTop = lanesBottom + TRACE_AXIS_GAP;
    drawTraceMarkers(gc,
                     graphLeft,
                     graphRight,
                     graphTop - TRACE_MARKER_HEIGHT,
                     isrTop,
                     axisTop + 8);
    drawMeasurementSelection(gc, graphLeft, graphRight, graphTop - TRACE_MARKER_HEIGHT, isrTop, axisTop + 8);
    drawIsrTracks(gc, graphLeft, graphRight, isrTop);

    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_DARK_GRAY));
    gc.drawLine(graphLeft, graphTop - 4, graphRight, graphTop - 4);

    int row = 0;
    for (TraceLane lane : traceGraphModel.lanes) {
      int y = graphTop + row * (TRACE_ROW_HEIGHT + TRACE_ROW_GAP);
      drawTraceLane(gc, lane, y, graphLeft, graphRight);
      row++;
    }

    drawTraceAxis(gc, graphLeft, graphRight, axisTop);
  }

  private void drawTraceLegend(GC gc, int x, int y) {

    int lineY = y + 12;

    drawLegendLine(gc, x, lineY, traceRunningColor, SWT.LINE_SOLID, 4, "Running");
    drawLegendLine(gc, x + 120, lineY, traceReadyColor, SWT.LINE_SOLID, 3, "Ready");
    drawLegendLine(gc, x + 220, lineY, traceSleepingColor, SWT.LINE_SOLID, 3, "Sleep/Wait");
    drawLegendLine(gc,
                   x + 360,
                   lineY,
                   traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_DARK_GRAY),
                   SWT.LINE_DOT,
                   1,
                   "Inactive");
  }

  private void drawLegendLine(GC gc,
                              int x,
                              int y,
                              Color color,
                              int style,
                              int width,
                              String label) {

    gc.setForeground(color);
    gc.setLineStyle(style);
    gc.setLineWidth(width);
    gc.drawLine(x, y, x + 36, y);
    gc.setLineStyle(SWT.LINE_SOLID);
    gc.setLineWidth(1);
    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_FOREGROUND));
    gc.drawText(label, x + 44, y - 8, true);
  }

  private void drawTraceMarkers(GC gc,
                                int graphLeft,
                                int graphRight,
                                int labelTop,
                                int lineTop,
                                int lineBottom) {
    int lastLabelX = Integer.MIN_VALUE;
    String lastLabel = "";

    renderedTraceMarkers.clear();

    for (TraceMarker marker : traceGraphModel.markers) {
      if ((marker.time < traceWindowStart) || (marker.time > traceWindowEnd))
        continue;
      int x = mapTraceTime(marker.time, graphLeft, graphRight);
      RenderedTraceMarker rendered = new RenderedTraceMarker();

      rendered.x = x;
      rendered.marker = marker;
      renderedTraceMarkers.add(rendered);

      gc.setForeground(traceMarkerColor);
      gc.setLineStyle(SWT.LINE_DASH);
      gc.setLineWidth(1);
      gc.drawLine(x, lineTop, x, lineBottom);
      gc.setLineStyle(SWT.LINE_SOLID);
      if (!marker.label.equals(lastLabel) && ((x - lastLabelX) >= 96)) {
        gc.drawText(marker.label, x + 4, labelTop, true);
        lastLabelX = x;
      }
      lastLabel = marker.label;
    }
  }

  private void drawMeasurementSelection(GC gc,
                                        int graphLeft,
                                        int graphRight,
                                        int labelTop,
                                        int lineTop,
                                        int lineBottom) {

    if (measurementStartMarker != null)
      drawMeasurementLine(gc, measurementStartMarker, "A", graphLeft, graphRight, labelTop, lineTop, lineBottom);
    if (measurementEndMarker != null)
      drawMeasurementLine(gc, measurementEndMarker, "B", graphLeft, graphRight, labelTop, lineTop, lineBottom);
  }

  private void drawMeasurementLine(GC gc,
                                   TraceMarker marker,
                                   String tag,
                                   int graphLeft,
                                   int graphRight,
                                   int labelTop,
                                   int lineTop,
                                   int lineBottom) {

    int x = mapTraceTime(marker.time, graphLeft, graphRight);
    Color oldForeground = gc.getForeground();
    Color oldBackground = gc.getBackground();
    int oldStyle = gc.getLineStyle();
    int oldWidth = gc.getLineWidth();
    int labelWidth;
    int labelHeight;
    int labelLeft;
    int labelTopY;
    int badgeBottomY;

    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_DARK_BLUE));
    gc.setLineStyle(SWT.LINE_SOLID);
    gc.setLineWidth(2);
    gc.drawLine(x, lineTop, x, lineBottom);

    labelWidth = gc.textExtent(tag).x;
    labelHeight = gc.textExtent(tag).y;
    labelLeft = x - (labelWidth / 2);
    badgeBottomY = lineTop - 4;
    labelTopY = badgeBottomY - labelHeight - 6;

    gc.setLineWidth(1);
    gc.setBackground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_BACKGROUND));
    gc.fillRoundRectangle(labelLeft - 4, labelTopY - 1, labelWidth + 8, labelHeight + 2, 6, 6);
    gc.drawRoundRectangle(labelLeft - 4, labelTopY - 1, labelWidth + 8, labelHeight + 2, 6, 6);
    gc.drawText(tag, labelLeft, labelTopY, true);
    gc.drawLine(x, badgeBottomY, x, lineTop);

    gc.setLineStyle(oldStyle);
    gc.setLineWidth(oldWidth);
    gc.setForeground(oldForeground);
    gc.setBackground(oldBackground);
  }

  private void updateTraceMarkerTooltip(int x, int y) {

    final int hitTolerance = 5;
    final int keepTolerance = 8;
    ArrayList<TraceMarker> matches = new ArrayList<TraceMarker>(TRACE_MARKER_TOOLTIP_LIMIT + 1);
    String details;
    RenderedTraceMarker anchor = null;

    if ((traceGraphCanvas == null) || traceGraphCanvas.isDisposed())
      return;

    if ((hoveredTraceMarker != null) && (Math.abs(hoveredTraceMarker.x - x) <= keepTolerance)) {
      showTraceMarkerToolTip(x, y, hoveredTraceMarkerText);
      return;
    }

    for (int i = renderedTraceMarkers.size() - 1; i >= 0; i--) {
      RenderedTraceMarker rendered = renderedTraceMarkers.get(i);

      if (Math.abs(rendered.x - x) <= hitTolerance) {
        if (anchor == null)
          anchor = rendered;
        matches.add(rendered.marker);
      }
    }

    if (!matches.isEmpty()) {
      details = makeTraceMarkerHoverText(matches);
      if ((hoveredTraceMarker != anchor) ||
          (hoveredTraceMarkerText == null) ||
          !hoveredTraceMarkerText.equals(details)) {
        hoveredTraceMarker = anchor;
        hoveredTraceMarkerText = details;
      }
      showTraceMarkerToolTip(x, y, hoveredTraceMarkerText);
      return;
    }

    clearTraceMarkerHover();
  }

  private String makeTraceMarkerHoverText(List<TraceMarker> markers) {

    StringBuilder sb = new StringBuilder(256);
    ArrayList<TraceMarker> sorted = new ArrayList<TraceMarker>(markers);
    int count;

    Collections.sort(sorted, (a, b) -> Integer.compare(b.eventIndex, a.eventIndex));
    count = Math.min(sorted.size(), TRACE_MARKER_TOOLTIP_LIMIT);

    for (int i = 0; i < count; i++) {
      if (i > 0)
        sb.append("\n\n");
      sb.append(sorted.get(i).details);
    }
    if (sorted.size() > count) {
      sb.append("\n\n");
      sb.append("+").append(sorted.size() - count).append(" more event");
      if ((sorted.size() - count) != 1)
        sb.append('s');
    }
    if ((measurementStartMarker != null) && !sorted.isEmpty()) {
      TraceMarker focus = sorted.get(0);
      if (focus.eventIndex != measurementStartMarker.eventIndex) {
        sb.append("\n\n");
        appendMeasurementText(sb, measurementStartMarker, focus, "A -> cursor");
      }
    }

    return sb.toString();
  }

  private void appendMeasurementText(StringBuilder sb,
                                     TraceMarker start,
                                     TraceMarker end,
                                     String title) {

    sb.append(title);
    sb.append('\n').append("A: event ").append(start.eventIndex);
    sb.append('\n').append("B: event ").append(end.eventIndex);
    sb.append('\n').append("dRT Stamp: ").append(end.time - start.time);
    sb.append('\n').append("dSysTime: ").append(end.sysTime - start.sysTime);
  }

  private String getMeasurementSummary() {

    StringBuilder sb = new StringBuilder(96);

    if (measurementStartMarker == null)
      return "";

    sb.append("  [A=").append(measurementStartMarker.eventIndex);
    if (measurementEndMarker != null) {
      sb.append(", B=").append(measurementEndMarker.eventIndex);
      sb.append(", dRT=").append(measurementEndMarker.time - measurementStartMarker.time);
      sb.append(", dSys=").append(measurementEndMarker.sysTime - measurementStartMarker.sysTime);
    }
    sb.append(']');

    return sb.toString();
  }

  private void clearTraceMarkerHover() {

    hoveredTraceMarker = null;
    hoveredTraceMarkerText = null;
    if ((traceMarkerToolTip != null) && !traceMarkerToolTip.isDisposed())
      traceMarkerToolTip.setVisible(false);
  }

  private RenderedTraceMarker findRenderedTraceMarkerAt(int x, int tolerance) {

    for (int i = renderedTraceMarkers.size() - 1; i >= 0; i--) {
      RenderedTraceMarker rendered = renderedTraceMarkers.get(i);

      if (Math.abs(rendered.x - x) <= tolerance)
        return rendered;
    }

    return null;
  }

  private void handleTraceMarkerClick(int x) {

    final int hitTolerance = 5;
    RenderedTraceMarker rendered = findRenderedTraceMarkerAt(x, hitTolerance);

    if (rendered == null) {
      if ((measurementStartMarker != null) || (measurementEndMarker != null)) {
        measurementStartMarker = null;
        measurementEndMarker = null;
        if ((traceGraphCanvas != null) && !traceGraphCanvas.isDisposed())
          traceGraphCanvas.redraw();
      }
      return;
    }

    if ((measurementStartMarker == null) || (measurementEndMarker != null)) {
      measurementStartMarker = rendered.marker;
      measurementEndMarker = null;
    }
    else if (measurementStartMarker.eventIndex == rendered.marker.eventIndex) {
      measurementStartMarker = null;
      measurementEndMarker = null;
    }
    else {
      measurementEndMarker = rendered.marker;
    }

    clearTraceMarkerHover();
    if ((traceGraphCanvas != null) && !traceGraphCanvas.isDisposed())
      traceGraphCanvas.redraw();
  }

  private void showTraceMarkerToolTip(int x, int y, String details) {

    if ((traceMarkerToolTip == null) || traceMarkerToolTip.isDisposed())
      return;
    if ((traceGraphCanvas == null) || traceGraphCanvas.isDisposed())
      return;

    traceMarkerToolTip.setText("Trace Event");
    traceMarkerToolTip.setMessage(details);
    {
      Point p = traceGraphCanvas.toDisplay(x + 16, y + 16);
      traceMarkerToolTip.setLocation(p);
    }
    traceMarkerToolTip.setVisible(true);
  }

  private void drawTraceLane(GC gc,
                             TraceLane lane,
                             int y,
                             int graphLeft,
                             int graphRight) {

    String label = makeTraceLaneLabel(lane);
    int runY = y + TRACE_TRACK_RUNNING_Y;
    int readyY = y + TRACE_TRACK_READY_Y;
    int sleepY = y + TRACE_TRACK_SLEEP_Y;

    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_FOREGROUND));
    gc.drawText(label, 12, y + 9, true);
    gc.drawText("Run", graphLeft - 48, runY - 8, true);
    gc.drawText("Rdy", graphLeft - 48, readyY - 8, true);
    gc.drawText("Slp", graphLeft - 48, sleepY - 8, true);

    drawDottedTraceSegment(gc, graphLeft, graphRight, runY);
    drawDottedTraceSegment(gc, graphLeft, graphRight, readyY);
    drawDottedTraceSegment(gc, graphLeft, graphRight, sleepY);

    for (TraceSegment segment : lane.segments) {
      int trackY = trackYForTraceKind(segment.kind, runY, readyY, sleepY);

      drawMappedSegment(gc,
                        graphLeft,
                        graphRight,
                        trackY,
                        segment.startTime,
                        segment.endTime,
                        colorForTraceState(segment.state),
                        lineWidthForTraceKind(segment.kind),
                        false);
    }

    drawTraceTransitions(gc, lane, graphLeft, graphRight, runY, readyY, sleepY);
    drawCondensedBreaks(gc, graphLeft, graphRight, runY);
    drawCondensedBreaks(gc, graphLeft, graphRight, readyY);
    drawCondensedBreaks(gc, graphLeft, graphRight, sleepY);

    gc.setLineStyle(SWT.LINE_SOLID);
    gc.setLineWidth(1);
  }

  private void drawIsrTracks(GC gc, int graphLeft, int graphRight, int top) {

    int row = 0;

    for (IsrLane lane : traceGraphModel.isrLanes) {
      int y = top + row * (TRACE_ISR_HEIGHT + TRACE_ISR_GAP);
      int lineY = y + TRACE_ISR_LINE_Y;

      gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_FOREGROUND));
      gc.drawText((row == 0) ? "ISR" : "", 12, y, true);
      gc.drawText(shortenLabel(lane.name, 14), graphLeft - 84, y, true);

      drawDottedTraceSegment(gc, graphLeft, graphRight, lineY);

      gc.setForeground(traceMarkerColor);
      for (TraceSegment segment : lane.segments) {
        drawMappedSegment(gc,
                          graphLeft,
                          graphRight,
                          lineY,
                          segment.startTime,
                          segment.endTime,
                          traceMarkerColor,
                          3,
                          true);
      }

      drawCondensedBreaks(gc, graphLeft, graphRight, lineY);

      gc.setLineStyle(SWT.LINE_SOLID);
      gc.setLineWidth(1);
      row++;
    }
  }

  private void drawTraceAxis(GC gc, int graphLeft, int graphRight, int axisTop) {

    int axisY = axisTop + 8;
    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_FOREGROUND));
    gc.drawText("Time", graphLeft - 48, axisTop, true);
    gc.drawLine(graphLeft, axisY, graphRight, axisY);

    drawCondensedBreaks(gc, graphLeft, graphRight, axisY);
    drawTraceAxisTicks(gc, graphLeft, graphRight, axisY);
  }

  private void drawDottedTraceSegment(GC gc, int x1, int x2, int y) {

    if (x2 <= x1)
      return;

    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_DARK_GRAY));
    gc.setLineStyle(SWT.LINE_DOT);
    gc.setLineWidth(1);
    gc.drawLine(x1, y, x2, y);
    gc.setLineStyle(SWT.LINE_SOLID);
    gc.setLineWidth(1);
  }

  private String makeTraceLaneLabel(TraceLane lane) {

    String label = makeHex(lane.address);

    if ((lane.name != null) && (lane.name.length() > 0) && (lane.name.compareTo("-") != 0))
      label = lane.name + "  " + label;

    return label;
  }

  private String shortenLabel(String s, int maxlen) {

    if (s == null)
      return "";
    if (s.length() <= maxlen)
      return s;
    if (maxlen <= 3)
      return s.substring(0, maxlen);

    return s.substring(0, maxlen - 3) + "...";
  }

  private int trackYForTraceKind(int kind, int runY, int readyY, int sleepY) {

    if (kind == TRACE_KIND_RUNNING)
      return runY;
    if (kind == TRACE_KIND_READY)
      return readyY;

    return sleepY;
  }

  private void drawTraceTransitions(GC gc,
                                    TraceLane lane,
                                    int graphLeft,
                                    int graphRight,
                                    int runY,
                                    int readyY,
                                    int sleepY) {

    if (lane.segments.size() < 2)
      return;

    gc.setLineStyle(SWT.LINE_SOLID);

    for (int i = 1; i < lane.segments.size(); i++) {
      TraceSegment previous = lane.segments.get(i - 1);
      TraceSegment current = lane.segments.get(i);
      int previousY = trackYForTraceKind(previous.kind, runY, readyY, sleepY);
      int currentY = trackYForTraceKind(current.kind, runY, readyY, sleepY);
      int lineWidth = Math.max(lineWidthForTraceKind(previous.kind),
                               lineWidthForTraceKind(current.kind));
      int x;

      if (previousY == currentY)
        continue;
      if ((current.startTime < traceWindowStart) || (current.startTime > traceWindowEnd))
        continue;

      x = mapTraceTime(current.startTime, graphLeft, graphRight);
      gc.setForeground(colorForTraceState(current.state));
      gc.setLineWidth(lineWidth);
      gc.drawLine(x, Math.min(previousY, currentY), x, Math.max(previousY, currentY));
    }

    gc.setLineWidth(1);
  }

  private void drawMappedSegment(GC gc,
                                 int graphLeft,
                                 int graphRight,
                                 int y,
                                 long rawStart,
                                 long rawEnd,
                                 Color color,
                                 int solidWidth,
                                 boolean expandTinySegment) {

    TimelineMapper mapper = traceTimelineMapper;

    if (mapper == null)
      return;

    for (TimelineSpan span : mapper.spans) {
      long segStart;
      long segEnd;
      int x1;
      int x2;

      if (rawEnd <= span.rawStart)
        break;
      if (rawStart >= span.rawEnd)
        continue;

      segStart = Math.max(rawStart, span.rawStart);
      segEnd = Math.min(rawEnd, span.rawEnd);
      if (segEnd < segStart)
        continue;

      x1 = mapTraceTime(segStart, graphLeft, graphRight);
      x2 = mapTraceTime(segEnd, graphLeft, graphRight);
      if (x2 <= x1) {
        if (!expandTinySegment)
          continue;

        int minWidth = Math.max(2, solidWidth);
        int halfWidth = (minWidth - 1) / 2;

        x1 = x1 - halfWidth;
        x2 = x1 + minWidth - 1;
        if (x1 < graphLeft) {
          x1 = graphLeft;
          x2 = x1 + minWidth - 1;
        }
        if (x2 > graphRight) {
          x2 = graphRight;
          x1 = x2 - minWidth + 1;
        }
      }

      gc.setForeground(color);
      if (span.condensedGap) {
        int breakX = mapDisplayTime((span.displayStart + span.displayEnd) / 2,
                                    mapper,
                                    graphLeft,
                                    graphRight);

        gc.setLineStyle(SWT.LINE_DOT);
        gc.setLineWidth(1);
        if (x1 < (breakX - TRACE_BREAK_CLEARANCE))
          gc.drawLine(x1, y, breakX - TRACE_BREAK_CLEARANCE, y);
        if ((breakX + TRACE_BREAK_CLEARANCE) < x2)
          gc.drawLine(breakX + TRACE_BREAK_CLEARANCE, y, x2, y);
      }
      else {
        gc.setLineStyle(SWT.LINE_SOLID);
        gc.setLineWidth(solidWidth);
        gc.drawLine(x1, y, x2, y);
      }
    }

    gc.setLineStyle(SWT.LINE_SOLID);
    gc.setLineWidth(1);
  }

  private void drawCondensedBreaks(GC gc, int graphLeft, int graphRight, int y) {

    TimelineMapper mapper = traceTimelineMapper;

    if (mapper == null)
      return;

    gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_LIST_FOREGROUND));
    gc.setLineStyle(SWT.LINE_SOLID);
    gc.setLineWidth(1);

    for (int i = 0; i < mapper.spans.size(); i++) {
      TimelineSpan span = mapper.spans.get(i);
      long displaySpan;
      long middleDisplay;

      if (!span.condensedGap)
        continue;
      if ((i == 0) || (i == (mapper.spans.size() - 1)))
        continue;

      displaySpan = span.displayEnd - span.displayStart;
      if (displaySpan <= 0)
        continue;

      middleDisplay = (span.displayStart + span.displayEnd) / 2;

      drawBreakMarker(gc,
                      mapDisplayTime(middleDisplay,
                                     mapper,
                                     graphLeft,
                                     graphRight),
                      y);
    }
  }

  private void drawBreakMarker(GC gc, int x, int y) {

    int x1 = x - TRACE_BREAK_GAP;
    int x2 = x + TRACE_BREAK_GAP;

    gc.drawLine(x1 - TRACE_BREAK_HALF_WIDTH,
                y + TRACE_BREAK_HALF_HEIGHT,
                x1 + TRACE_BREAK_HALF_WIDTH,
                y - TRACE_BREAK_HALF_HEIGHT);
    gc.drawLine(x2 - TRACE_BREAK_HALF_WIDTH,
                y + TRACE_BREAK_HALF_HEIGHT,
                x2 + TRACE_BREAK_HALF_WIDTH,
                y - TRACE_BREAK_HALF_HEIGHT);
  }

  private int mapTraceTime(long time, int graphLeft, int graphRight) {

    TimelineMapper mapper = traceTimelineMapper;
    long displayTime;
    int width = graphRight - graphLeft;

    if ((mapper == null) || (width <= 0))
      return graphLeft;
    displayTime = mapToDisplayTime(time, mapper);

    return mapDisplayTime(displayTime, mapper, graphLeft, graphRight);
  }

  private int mapDisplayTime(long displayTime, TimelineMapper mapper, int graphLeft, int graphRight) {

    long span = mapper.displaySpan;
    int width = graphRight - graphLeft;

    if ((span <= 0) || (width <= 0))
      return graphLeft;

    return graphLeft + (int)((displayTime * width) / span);
  }

  private long mapToDisplayTime(long time, TimelineMapper mapper) {

    TimelineSpan last = null;

    for (TimelineSpan span : mapper.spans) {
      long rawSpan;
      long displaySpan;

      last = span;
      if (time < span.rawStart)
        return span.displayRawStart;
      if (time > span.rawEnd)
        continue;

      rawSpan = span.rawEnd - span.rawStart;
      displaySpan = span.displayRawEnd - span.displayRawStart;
      if (rawSpan <= 0)
        return span.displayRawStart;
      if (time == span.rawEnd)
        return span.displayRawEnd;

      return span.displayRawStart +
             ((time - span.rawStart) * displaySpan) / rawSpan;
    }

    if (last != null)
      return last.displayRawEnd;

    return 0;
  }

  private void drawTraceAxisTicks(GC gc, int graphLeft, int graphRight, int axisY) {

    TimelineMapper mapper = traceTimelineMapper;
    Font originalFont = gc.getFont();
    Font secondaryFont = SWTResourceManager.getFont("Sans", 7, SWT.NORMAL);
    Color originalForeground = gc.getForeground();
    int lastLabelRight = Integer.MIN_VALUE;

    if (mapper == null)
      return;

    for (int i = 0; i < mapper.axisTicks.size(); i++) {
      Long tick = mapper.axisTicks.get(i);
      long time = tick.longValue();
      int x = mapTraceTime(time, graphLeft, graphRight);
      String label = Long.toString(time);
      String sysLabel = "(" + estimateSysTimeLabel(time) + ")";
      int labelWidth = gc.textExtent(label).x;
      int sysLabelWidth;
      int labelLeft = x - (labelWidth / 2);
      int sysLabelLeft;
      boolean forceLabel = (i == 0) || (i == (mapper.axisTicks.size() - 1));

      if (labelLeft < graphLeft)
        labelLeft = graphLeft;
      if ((labelLeft + labelWidth) > graphRight)
        labelLeft = graphRight - labelWidth;

      gc.drawLine(x, axisY - 4, x, axisY + 4);
      if (forceLabel || ((labelLeft - lastLabelRight) >= 12)) {
        gc.drawText(label, labelLeft, axisY + 6, true);
        gc.setFont(secondaryFont);
        gc.setForeground(traceGraphCanvas.getDisplay().getSystemColor(SWT.COLOR_DARK_GRAY));
        sysLabelWidth = gc.textExtent(sysLabel).x;
        sysLabelLeft = x - (sysLabelWidth / 2);
        if (sysLabelLeft < graphLeft)
          sysLabelLeft = graphLeft;
        if ((sysLabelLeft + sysLabelWidth) > graphRight)
          sysLabelLeft = graphRight - sysLabelWidth;
        gc.drawText(sysLabel, sysLabelLeft, axisY + 20, true);
        gc.setFont(originalFont);
        gc.setForeground(originalForeground);
        lastLabelRight = labelLeft + labelWidth;
      }
    }
  }

  private String estimateSysTimeLabel(long time) {

    TraceGraphModel model = traceGraphModel;
    TraceMarker previous = null;

    if ((model == null) || model.markers.isEmpty())
      return "-";

    for (TraceMarker marker : model.markers) {
      if (marker.time == time)
        return Long.toString(marker.sysTime);
      if (marker.time > time) {
        if (previous == null)
          return Long.toString(marker.sysTime);
        return Long.toString(interpolateSysTime(previous, marker, time));
      }
      previous = marker;
    }

    return Long.toString(previous.sysTime);
  }

  private long interpolateSysTime(TraceMarker previous, TraceMarker next, long time) {

    long rtSpan = next.time - previous.time;

    if (rtSpan <= 0)
      return next.sysTime;

    return previous.sysTime +
           ((time - previous.time) * (next.sysTime - previous.sysTime)) / rtSpan;
  }

  private void populateAxisTicks(TimelineMapper mapper) {

    mapper.axisTicks.add(Long.valueOf(mapper.windowStart));
    for (int i = 1; i < TRACE_AXIS_TICKS; i++) {
      long time = mapper.windowStart +
                  ((mapper.windowEnd - mapper.windowStart) * i) / TRACE_AXIS_TICKS;
      mapper.axisTicks.add(Long.valueOf(time));
    }
    mapper.axisTicks.add(Long.valueOf(mapper.windowEnd));
  }

  private int lineWidthForTraceKind(int kind) {

    if (kind == TRACE_KIND_RUNNING)
      return 4;
    if (kind == TRACE_KIND_READY)
      return 3;

    return 3;
  }

  private Color colorForTraceState(String state) {

    if ("CURRENT".equals(state))
      return traceRunningColor;
    if ("READY".equals(state))
      return traceReadyColor;
    if ("WTSEM".equals(state))
      return traceWtSemColor;
    if ("WTMTX".equals(state))
      return traceWtMtxColor;
    if ("WTCOND".equals(state))
      return traceWtCondColor;
    if ("WTMSG".equals(state) || "SNDMSG".equals(state) || "SNDMSGQ".equals(state))
      return traceWtMsgColor;
    if ("WTANDEVT".equals(state) || "WTOREVT".equals(state))
      return traceWtEvtColor;

    return traceSleepingColor;
  }

  /**
   * Passing the focus request to the viewer's control.
   */
  public void setFocus() {
    tabFolder.setFocus();
  }

  @Override
  public void dispose() {

    disposeColor(traceRunningColor);
    disposeColor(traceReadyColor);
    disposeColor(traceSleepingColor);
    disposeColor(traceWtSemColor);
    disposeColor(traceWtMtxColor);
    disposeColor(traceWtCondColor);
    disposeColor(traceWtMsgColor);
    disposeColor(traceWtEvtColor);
    disposeColor(traceMarkerColor);

    super.dispose();
  }

  private void disposeColor(Color color) {

    if ((color != null) && !color.isDisposed())
      color.dispose();
  }

  private static class TraceGraphModel {

    boolean hasEvents;
    long minTime;
    long maxTime;
    List<IsrLane> isrLanes = new ArrayList<IsrLane>(8);
    List<TraceLane> lanes = new ArrayList<TraceLane>(16);
    List<TraceMarker> markers = new ArrayList<TraceMarker>(16);
  }

  private static class IsrLane {

    String name;
    List<TraceSegment> segments = new ArrayList<TraceSegment>(8);
  }

  private static class TraceLane {

    String address;
    String name;
    long firstSeen = Long.MAX_VALUE;
    boolean terminated;
    long terminateTime = Long.MAX_VALUE;
    TraceSegment segment;
    List<TraceSegment> segments = new ArrayList<TraceSegment>(8);
  }

  private static class TraceSegment {

    long startTime;
    long endTime;
    int kind;
    String state;
  }

  private static class TraceMarker {

    int eventIndex;
    long time;
    long sysTime;
    String label;
    String details;
  }

  private static class RenderedTraceMarker {

    int x;
    TraceMarker marker;
  }

  private static class TimelineMapper {

    long windowStart;
    long windowEnd;
    long displaySpan;
    List<Long> axisTicks = new ArrayList<Long>(16);
    List<TimelineSpan> spans = new ArrayList<TimelineSpan>(32);
  }

  private static class TimelineSpan {

    long rawStart;
    long rawEnd;
    long displayStart;
    long displayEnd;
    long displayRawStart;
    long displayRawEnd;
    boolean condensedGap;
  }

  private static class TimeCluster {

    final long startTime;
    final long endTime;

    TimeCluster(long startTime, long endTime) {

      this.startTime = startTime;
      this.endTime = endTime;
    }
  }
}
