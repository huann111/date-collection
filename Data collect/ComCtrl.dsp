# Microsoft Developer Studio Project File - Name="ComCtrl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ComCtrl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComCtrl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComCtrl.mak" CFG="ComCtrl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComCtrl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ComCtrl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComCtrl - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SkinPPWTL.lib /nologo /subsystem:windows /machine:I386 /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ComCtrl - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SkinPPWTL.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ComCtrl - Win32 Release"
# Name "ComCtrl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChangeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartAxisLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartBarSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCandlestickSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCrossHairCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartDateTimeAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartDragLineCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartFont.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartGanttSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartGradient.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLineSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLogarithmicAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartPointsSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartStandardAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartSurfaceSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartXYSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\Com.cpp
# End Source File
# Begin Source File

SOURCE=.\ComCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComCtrl.rc
# End Source File
# Begin Source File

SOURCE=.\ComCtrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PassDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChangeDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartAxisLabel.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartBalloonLabel.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartBalloonLabel.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartBarSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCandlestickSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCrossHairCursor.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartCursor.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartDateTimeAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartDragLineCursor.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartFont.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartGanttSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartGradient.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartGrid.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLabel.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLabel.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLegend.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLineSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartLogarithmicAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartMouseListener.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartPointsArray.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartPointsArray.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartPointsSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartSerieBase.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartSerieBase.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartSeriesMouseListener.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartStandardAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartString.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartSurfaceSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartTitle.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\ChartXYSerie.h
# End Source File
# Begin Source File

SOURCE=.\Com.h
# End Source File
# Begin Source File

SOURCE=.\ComCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ComCtrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\PassDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl_source\PointsOrdering.h
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SkinPPWTL.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\00.bmp
# End Source File
# Begin Source File

SOURCE=.\res\12345.bmp
# End Source File
# Begin Source File

SOURCE=.\res\455.bmp
# End Source File
# Begin Source File

SOURCE=.\res\45546.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ComCtrl.ico
# End Source File
# Begin Source File

SOURCE=.\res\ComCtrl.rc2
# End Source File
# Begin Source File

SOURCE=.\res\gfdgd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rss.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ComCtrl : {B6C10497-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CImport
# 	2:10:HeaderFile:import.h
# 	2:8:ImplFile:import.cpp
# End Section
# Section ComCtrl : {FDB6AE9B-AE83-4CC3-AC6D-03CF0E133867}
# 	2:5:Class:CPyramidSeries
# 	2:10:HeaderFile:pyramidseries.h
# 	2:8:ImplFile:pyramidseries.cpp
# End Section
# Section ComCtrl : {B6C1053B-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CImageBarSeries
# 	2:10:HeaderFile:imagebarseries.h
# 	2:8:ImplFile:imagebarseries.cpp
# End Section
# Section ComCtrl : {235FB744-F8ED-11D4-93C8-006008A7EED4}
# 	2:5:Class:CPNGExport
# 	2:10:HeaderFile:pngexport.h
# 	2:8:ImplFile:pngexport.cpp
# End Section
# Section ComCtrl : {B6C104EA-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CMovingAvgFunction
# 	2:10:HeaderFile:movingavgfunction.h
# 	2:8:ImplFile:movingavgfunction.cpp
# End Section
# Section ComCtrl : {B6C1048E-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CStrings
# 	2:10:HeaderFile:strings.h
# 	2:8:ImplFile:strings.cpp
# End Section
# Section ComCtrl : {EC0AB1C0-6CAB-11CF-8998-00AA00688B10}
# 	2:5:Class:CControls
# 	2:10:HeaderFile:controls.h
# 	2:8:ImplFile:controls.cpp
# End Section
# Section ComCtrl : {B6C104AA-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPage
# 	2:10:HeaderFile:page.h
# 	2:8:ImplFile:page.cpp
# End Section
# Section ComCtrl : {612A8624-0FB3-11CE-8747-524153480004}
# 	2:21:DefaultSinkHeaderFile:toolbar.h
# 	2:16:DefaultSinkClass:CToolbar
# End Section
# Section ComCtrl : {C9F8E464-0B4B-4427-8678-363CF8E1955D}
# 	2:5:Class:CColorBandTool
# 	2:10:HeaderFile:colorbandtool.h
# 	2:8:ImplFile:colorbandtool.cpp
# End Section
# Section ComCtrl : {662C9054-0898-4F09-881E-5ABB47978FB6}
# 	2:5:Class:CRMSFunction
# 	2:10:HeaderFile:rmsfunction.h
# 	2:8:ImplFile:rmsfunction.cpp
# End Section
# Section ComCtrl : {B6C10508-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CSurfaceSeries
# 	2:10:HeaderFile:surfaceseries.h
# 	2:8:ImplFile:surfaceseries.cpp
# End Section
# Section ComCtrl : {4CC67466-2A11-45C6-924E-15E8B9F6B780}
# 	2:5:Class:CWaterfallSeries
# 	2:10:HeaderFile:waterfallseries.h
# 	2:8:ImplFile:waterfallseries.cpp
# End Section
# Section ComCtrl : {A77491E3-F825-11D4-93C7-006008A7EED4}
# 	2:5:Class:CJPEGExport
# 	2:10:HeaderFile:jpegexport.h
# 	2:8:ImplFile:jpegexport.cpp
# End Section
# Section ComCtrl : {5970102E-E487-4B12-88A8-A7930EF23E5D}
# 	2:5:Class:CDrawLineTool
# 	2:10:HeaderFile:drawlinetool.h
# 	2:8:ImplFile:drawlinetool.cpp
# End Section
# Section ComCtrl : {235FB74B-F8ED-11D4-93C8-006008A7EED4}
# 	2:5:Class:CPCXExport
# 	2:10:HeaderFile:pcxexport.h
# 	2:8:ImplFile:pcxexport.cpp
# End Section
# Section ComCtrl : {B6C104C7-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CGanttSeries
# 	2:10:HeaderFile:ganttseries.h
# 	2:8:ImplFile:ganttseries.cpp
# End Section
# Section ComCtrl : {AC690ACD-0730-11D5-93E3-006008A7EED4}
# 	2:5:Class:CNativeExport
# 	2:10:HeaderFile:nativeexport.h
# 	2:8:ImplFile:nativeexport.cpp
# End Section
# Section ComCtrl : {B6C10538-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CTeeOpenGL
# 	2:10:HeaderFile:teeopengl.h
# 	2:8:ImplFile:teeopengl.cpp
# End Section
# Section ComCtrl : {B6C104AE-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CMarks
# 	2:10:HeaderFile:marks.h
# 	2:8:ImplFile:marks.cpp
# End Section
# Section ComCtrl : {A841A3E5-3ED7-11D5-943D-006008A7EED4}
# 	2:5:Class:CValueLists
# 	2:10:HeaderFile:valuelists.h
# 	2:8:ImplFile:valuelists.cpp
# End Section
# Section ComCtrl : {E517CB27-1C48-11D5-9400-006008A7EED4}
# 	2:5:Class:CCalendarCellUpper
# 	2:10:HeaderFile:calendarcellupper.h
# 	2:8:ImplFile:calendarcellupper.cpp
# End Section
# Section ComCtrl : {B6C104A7-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CWalls
# 	2:10:HeaderFile:walls.h
# 	2:8:ImplFile:walls.cpp
# End Section
# Section ComCtrl : {BA3A0E2D-CCE7-4CF6-82D2-044B2A64EE59}
# 	2:5:Class:CColorGridSeries
# 	2:10:HeaderFile:colorgridseries.h
# 	2:8:ImplFile:colorgridseries.cpp
# End Section
# Section ComCtrl : {B6C104C2-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CFastLineSeries
# 	2:10:HeaderFile:fastlineseries.h
# 	2:8:ImplFile:fastlineseries.cpp
# End Section
# Section ComCtrl : {235FB74F-F8ED-11D4-93C8-006008A7EED4}
# 	2:5:Class:CBMPExport
# 	2:10:HeaderFile:bmpexport.h
# 	2:8:ImplFile:bmpexport.cpp
# End Section
# Section ComCtrl : {E517CB2E-1C48-11D5-9400-006008A7EED4}
# 	2:5:Class:CPageNumTool
# 	2:10:HeaderFile:pagenumtool.h
# 	2:8:ImplFile:pagenumtool.cpp
# End Section
# Section ComCtrl : {B6C10533-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CTeePoint2D
# 	2:10:HeaderFile:teepoint2d.h
# 	2:8:ImplFile:teepoint2d.cpp
# End Section
# Section ComCtrl : {B6C1050A-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CSeriesMarkPosition
# 	2:10:HeaderFile:seriesmarkposition.h
# 	2:8:ImplFile:seriesmarkposition.cpp
# End Section
# Section ComCtrl : {B6C1053A-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CWindRoseSeries
# 	2:10:HeaderFile:windroseseries.h
# 	2:8:ImplFile:windroseseries.cpp
# End Section
# Section ComCtrl : {CB0CE331-76CB-449C-9BE7-FB69C03C3439}
# 	2:5:Class:CHorizBoxPlotSeries
# 	2:10:HeaderFile:horizboxplotseries.h
# 	2:8:ImplFile:horizboxplotseries.cpp
# End Section
# Section ComCtrl : {AC690AD1-0730-11D5-93E3-006008A7EED4}
# 	2:5:Class:CXMLExport
# 	2:10:HeaderFile:xmlexport.h
# 	2:8:ImplFile:xmlexport.cpp
# End Section
# Section ComCtrl : {B6C10496-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CExport
# 	2:10:HeaderFile:export.h
# 	2:8:ImplFile:export.cpp
# End Section
# Section ComCtrl : {235FB753-F8ED-11D4-93C8-006008A7EED4}
# 	2:5:Class:CMarksTipTool
# 	2:10:HeaderFile:markstiptool.h
# 	2:8:ImplFile:markstiptool.cpp
# End Section
# Section ComCtrl : {B6C1048D-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CBrush1
# 	2:10:HeaderFile:brush.h
# 	2:8:ImplFile:brush.cpp
# End Section
# Section ComCtrl : {3B2B9817-FBBF-11D4-93CA-006008A7EED4}
# 	2:5:Class:CTitles
# 	2:10:HeaderFile:titles.h
# 	2:8:ImplFile:titles.cpp
# End Section
# Section ComCtrl : {AC690AD5-0730-11D5-93E3-006008A7EED4}
# 	2:5:Class:CHTMLExport
# 	2:10:HeaderFile:htmlexport.h
# 	2:8:ImplFile:htmlexport.cpp
# End Section
# Section ComCtrl : {7791BA40-E020-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CButtons
# 	2:10:HeaderFile:buttons.h
# 	2:8:ImplFile:buttons.cpp
# End Section
# Section ComCtrl : {B6C10507-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPoint3DSeries
# 	2:10:HeaderFile:point3dseries.h
# 	2:8:ImplFile:point3dseries.cpp
# End Section
# Section ComCtrl : {2DCBF4FF-BEDF-4140-B726-70996BB2B6E6}
# 	2:5:Class:CBollingerFunction
# 	2:10:HeaderFile:bollingerfunction.h
# 	2:8:ImplFile:bollingerfunction.cpp
# End Section
# Section ComCtrl : {B6C104A6-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CWall
# 	2:10:HeaderFile:wall.h
# 	2:8:ImplFile:wall.cpp
# End Section
# Section ComCtrl : {22A5D9BB-B643-11D5-94F8-006008A7EED4}
# 	2:5:Class:CTeeShapePanel
# 	2:10:HeaderFile:teeshapepanel.h
# 	2:8:ImplFile:teeshapepanel.cpp
# End Section
# Section ComCtrl : {62DD8657-F041-11D4-93B1-006008A7EED4}
# 	2:5:Class:CDrawLineList
# 	2:10:HeaderFile:drawlinelist.h
# 	2:8:ImplFile:drawlinelist.cpp
# End Section
# Section ComCtrl : {B6C1050E-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CStdDeviationFunction
# 	2:10:HeaderFile:stddeviationfunction.h
# 	2:8:ImplFile:stddeviationfunction.cpp
# End Section
# Section ComCtrl : {B6C10491-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CAxes
# 	2:10:HeaderFile:axes.h
# 	2:8:ImplFile:axes.cpp
# End Section
# Section ComCtrl : {B6C10512-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CEnvironment
# 	2:10:HeaderFile:environment.h
# 	2:8:ImplFile:environment.cpp
# End Section
# Section ComCtrl : {B6C104BD-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPointer
# 	2:10:HeaderFile:pointer.h
# 	2:8:ImplFile:pointer.cpp
# End Section
# Section ComCtrl : {B6C104AD-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CTeeFunction
# 	2:10:HeaderFile:teefunction.h
# 	2:8:ImplFile:teefunction.cpp
# End Section
# Section ComCtrl : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section ComCtrl : {C793DB5D-E235-4248-87AD-E436822E64F2}
# 	2:5:Class:CHorizLineSeries
# 	2:10:HeaderFile:horizlineseries.h
# 	2:8:ImplFile:horizlineseries.cpp
# End Section
# Section ComCtrl : {01E6D0D8-07EE-11D5-93E4-006008A7EED4}
# 	2:5:Class:CFunnelSeries
# 	2:10:HeaderFile:funnelseries.h
# 	2:8:ImplFile:funnelseries.cpp
# End Section
# Section ComCtrl : {B6C104C6-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CAxis
# 	2:10:HeaderFile:axis.h
# 	2:8:ImplFile:axis.cpp
# End Section
# Section ComCtrl : {B6C10485-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CTChart
# 	2:10:HeaderFile:tchart.h
# 	2:8:ImplFile:tchart.cpp
# End Section
# Section ComCtrl : {41A5C203-7F36-4E11-840D-D41230760D8E}
# 	2:5:Class:CDonutSeries
# 	2:10:HeaderFile:donutseries.h
# 	2:8:ImplFile:donutseries.cpp
# End Section
# Section ComCtrl : {01E6D0DA-07EE-11D5-93E4-006008A7EED4}
# 	2:5:Class:CCalendarSeries
# 	2:10:HeaderFile:calendarseries.h
# 	2:8:ImplFile:calendarseries.cpp
# End Section
# Section ComCtrl : {B6C104ED-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPieOtherSlice
# 	2:10:HeaderFile:pieotherslice.h
# 	2:8:ImplFile:pieotherslice.cpp
# End Section
# Section ComCtrl : {B6C104C1-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CLineSeries
# 	2:10:HeaderFile:lineseries.h
# 	2:8:ImplFile:lineseries.cpp
# End Section
# Section ComCtrl : {DA944291-24C8-4956-BEE4-3129A675A49C}
# 	2:5:Class:CBarJoinSeries
# 	2:10:HeaderFile:barjoinseries.h
# 	2:8:ImplFile:barjoinseries.cpp
# End Section
# Section ComCtrl : {F66470FB-1309-47FF-A790-26E2E38BEBD0}
# 	2:5:Class:CContourLevels
# 	2:10:HeaderFile:contourlevels.h
# 	2:8:ImplFile:contourlevels.cpp
# End Section
# Section ComCtrl : {B6C10490-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CAspect
# 	2:10:HeaderFile:aspect.h
# 	2:8:ImplFile:aspect.cpp
# End Section
# Section ComCtrl : {97763CEC-4D57-4612-A799-05C6E19AC789}
# 	2:5:Class:CRotateTool
# 	2:10:HeaderFile:rotatetool.h
# 	2:8:ImplFile:rotatetool.cpp
# End Section
# Section ComCtrl : {B6C10506-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CErrorSeries
# 	2:10:HeaderFile:errorseries.h
# 	2:8:ImplFile:errorseries.cpp
# End Section
# Section ComCtrl : {0B304B42-253F-4221-8C87-8AD1FCA76C94}
# 	2:5:Class:CContourLevel
# 	2:10:HeaderFile:contourlevel.h
# 	2:8:ImplFile:contourlevel.cpp
# End Section
# Section ComCtrl : {33A0CF4E-AE1F-43DB-A3CF-B7F9905085C8}
# 	2:5:Class:CMapSeries
# 	2:10:HeaderFile:mapseries.h
# 	2:8:ImplFile:mapseries.cpp
# End Section
# Section ComCtrl : {AC690AD9-0730-11D5-93E3-006008A7EED4}
# 	2:5:Class:CMapPolygonList
# 	2:10:HeaderFile:mappolygonlist.h
# 	2:8:ImplFile:mappolygonlist.cpp
# End Section
# Section ComCtrl : {B6C104A5-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPrinter
# 	2:10:HeaderFile:printer.h
# 	2:8:ImplFile:printer.cpp
# End Section
# Section ComCtrl : {E517CB25-1C48-11D5-9400-006008A7EED4}
# 	2:5:Class:CCalendarCell
# 	2:10:HeaderFile:calendarcell.h
# 	2:8:ImplFile:calendarcell.cpp
# End Section
# Section ComCtrl : {AC690ADB-0730-11D5-93E3-006008A7EED4}
# 	2:5:Class:CMapPolygon
# 	2:10:HeaderFile:mappolygon.h
# 	2:8:ImplFile:mappolygon.cpp
# End Section
# Section ComCtrl : {B6C104C5-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CBubbleSeries
# 	2:10:HeaderFile:bubbleseries.h
# 	2:8:ImplFile:bubbleseries.cpp
# End Section
# Section ComCtrl : {B6C10501-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CExplodedSlices
# 	2:10:HeaderFile:explodedslices.h
# 	2:8:ImplFile:explodedslices.cpp
# End Section
# Section ComCtrl : {B6C104AC-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CSeries
# 	2:10:HeaderFile:series.h
# 	2:8:ImplFile:series.cpp
# End Section
# Section ComCtrl : {CC476B13-71AC-463F-85E4-0AA8DD8B8BDE}
# 	2:5:Class:CLegendSymbol
# 	2:10:HeaderFile:legendsymbol.h
# 	2:8:ImplFile:legendsymbol.cpp
# End Section
# Section ComCtrl : {2EB35E28-80CF-4F35-9B6B-427E2AC1BFA6}
# 	2:5:Class:CNearestTool
# 	2:10:HeaderFile:nearesttool.h
# 	2:8:ImplFile:nearesttool.cpp
# End Section
# Section ComCtrl : {B6C104DC-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CCandleSeries
# 	2:10:HeaderFile:candleseries.h
# 	2:8:ImplFile:candleseries.cpp
# End Section
# Section ComCtrl : {5B9827E5-3BE4-4DA3-9A6F-611BF900E4E1}
# 	2:5:Class:CTriSurfaceSeries
# 	2:10:HeaderFile:trisurfaceseries.h
# 	2:8:ImplFile:trisurfaceseries.cpp
# End Section
# Section ComCtrl : {B6C104C0-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPointSeries
# 	2:10:HeaderFile:pointseries.h
# 	2:8:ImplFile:pointseries.cpp
# End Section
# Section ComCtrl : {235FB74D-F8ED-11D4-93C8-006008A7EED4}
# 	2:5:Class:CMetafileExport
# 	2:10:HeaderFile:metafileexport.h
# 	2:8:ImplFile:metafileexport.cpp
# End Section
# Section ComCtrl : {DFBF9393-46FD-11D2-AEC3-00400141862D}
# 	2:5:Class:CContourSeries
# 	2:10:HeaderFile:contourseries.h
# 	2:8:ImplFile:contourseries.cpp
# End Section
# Section ComCtrl : {B6C104E5-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CAverageFunction
# 	2:10:HeaderFile:averagefunction.h
# 	2:8:ImplFile:averagefunction.cpp
# End Section
# Section ComCtrl : {B6C10489-FB89-11D4-93C9-006008A7EED4}
# 	2:21:DefaultSinkHeaderFile:tchart.h
# 	2:16:DefaultSinkClass:CTChart
# End Section
# Section ComCtrl : {235FB746-F8ED-11D4-93C8-006008A7EED4}
# 	2:5:Class:CGIFExport
# 	2:10:HeaderFile:gifexport.h
# 	2:8:ImplFile:gifexport.cpp
# End Section
# Section ComCtrl : {B6C10494-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CAxisTitle
# 	2:10:HeaderFile:axistitle.h
# 	2:8:ImplFile:axistitle.cpp
# End Section
# Section ComCtrl : {E6E17E8C-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CToolbar
# 	2:10:HeaderFile:toolbar.h
# 	2:8:ImplFile:toolbar.cpp
# End Section
# Section ComCtrl : {B6C1048B-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPen1
# 	2:10:HeaderFile:pen.h
# 	2:8:ImplFile:pen.cpp
# End Section
# Section ComCtrl : {B6C104A9-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CGradient
# 	2:10:HeaderFile:gradient.h
# 	2:8:ImplFile:gradient.cpp
# End Section
# Section ComCtrl : {5101D067-AD02-426B-832E-A898AF6E4F5E}
# 	2:5:Class:CTeeShadow
# 	2:10:HeaderFile:teeshadow.h
# 	2:8:ImplFile:teeshadow.cpp
# End Section
# Section ComCtrl : {B6C104E0-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CVolumeSeries
# 	2:10:HeaderFile:volumeseries.h
# 	2:8:ImplFile:volumeseries.cpp
# End Section
# Section ComCtrl : {E517CB29-1C48-11D5-9400-006008A7EED4}
# 	2:5:Class:CAnnotationTool
# 	2:10:HeaderFile:annotationtool.h
# 	2:8:ImplFile:annotationtool.cpp
# End Section
# Section ComCtrl : {B6C104C9-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CArrowSeries
# 	2:10:HeaderFile:arrowseries.h
# 	2:8:ImplFile:arrowseries.cpp
# End Section
# Section ComCtrl : {B6C10505-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CRadarSeries
# 	2:10:HeaderFile:radarseries.h
# 	2:8:ImplFile:radarseries.cpp
# End Section
# Section ComCtrl : {B6C104A4-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CZoom
# 	2:10:HeaderFile:zoom.h
# 	2:8:ImplFile:zoom.cpp
# End Section
# Section ComCtrl : {67D7AA1C-12FA-4F34-8EB2-B3E8646E0E5F}
# 	2:5:Class:CTools
# 	2:10:HeaderFile:tools.h
# 	2:8:ImplFile:tools.cpp
# End Section
# Section ComCtrl : {B6C104E9-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CExpAvgFunction
# 	2:10:HeaderFile:expavgfunction.h
# 	2:8:ImplFile:expavgfunction.cpp
# End Section
# Section ComCtrl : {AC690AD3-0730-11D5-93E3-006008A7EED4}
# 	2:5:Class:CXLSExport
# 	2:10:HeaderFile:xlsexport.h
# 	2:8:ImplFile:xlsexport.cpp
# End Section
# Section ComCtrl : {B6C104AB-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPanel
# 	2:10:HeaderFile:panel.h
# 	2:8:ImplFile:panel.cpp
# End Section
# Section ComCtrl : {B6C104C4-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPieSeries
# 	2:10:HeaderFile:pieseries.h
# 	2:8:ImplFile:pieseries.cpp
# End Section
# Section ComCtrl : {C746269F-0A39-4EC5-B52F-7E489835035B}
# 	2:5:Class:CAxisArrowTool
# 	2:10:HeaderFile:axisarrowtool.h
# 	2:8:ImplFile:axisarrowtool.cpp
# End Section
# Section ComCtrl : {69A3C18D-728E-47B5-9144-7C58B59AA42D}
# 	2:5:Class:CSmithSeries
# 	2:10:HeaderFile:smithseries.h
# 	2:8:ImplFile:smithseries.cpp
# End Section
# Section ComCtrl : {B6C1053C-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CBar3DSeries
# 	2:10:HeaderFile:bar3dseries.h
# 	2:8:ImplFile:bar3dseries.cpp
# End Section
# Section ComCtrl : {B6C10510-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CRSIFunction
# 	2:10:HeaderFile:rsifunction.h
# 	2:8:ImplFile:rsifunction.cpp
# End Section
# Section ComCtrl : {B6C104CB-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CBarSeries
# 	2:10:HeaderFile:barseries.h
# 	2:8:ImplFile:barseries.cpp
# End Section
# Section ComCtrl : {B6C1050C-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CCircleLabels
# 	2:10:HeaderFile:circlelabels.h
# 	2:8:ImplFile:circlelabels.cpp
# End Section
# Section ComCtrl : {B4B8B973-32BF-40A8-8E07-EFBA557E13F8}
# 	2:5:Class:CHighLowSeries
# 	2:10:HeaderFile:highlowseries.h
# 	2:8:ImplFile:highlowseries.cpp
# End Section
# Section ComCtrl : {B6C104EB-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CChartFont
# 	2:10:HeaderFile:chartfont.h
# 	2:8:ImplFile:chartfont.cpp
# End Section
# Section ComCtrl : {B6C1048F-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CCanvas
# 	2:10:HeaderFile:canvas.h
# 	2:8:ImplFile:canvas.cpp
# End Section
# Section ComCtrl : {3B2B9819-FBBF-11D4-93CA-006008A7EED4}
# 	2:5:Class:CTeeFont
# 	2:10:HeaderFile:teefont.h
# 	2:8:ImplFile:teefont.cpp
# End Section
# Section ComCtrl : {2E375632-A81D-400A-9369-F609B6B914AC}
# 	2:5:Class:CBoxPlotSeries
# 	2:10:HeaderFile:boxplotseries.h
# 	2:8:ImplFile:boxplotseries.cpp
# End Section
# Section ComCtrl : {B6C10493-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CAxisLabels
# 	2:10:HeaderFile:axislabels.h
# 	2:8:ImplFile:axislabels.cpp
# End Section
# Section ComCtrl : {235FB755-F8ED-11D4-93C8-006008A7EED4}
# 	2:5:Class:CChartImageTool
# 	2:10:HeaderFile:chartimagetool.h
# 	2:8:ImplFile:chartimagetool.cpp
# End Section
# Section ComCtrl : {B6C104DB-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CHorizBarSeries
# 	2:10:HeaderFile:horizbarseries.h
# 	2:8:ImplFile:horizbarseries.cpp
# End Section
# Section ComCtrl : {B6C104A8-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CLegend
# 	2:10:HeaderFile:legend.h
# 	2:8:ImplFile:legend.cpp
# End Section
# Section ComCtrl : {AC690AD7-0730-11D5-93E3-006008A7EED4}
# 	2:5:Class:CTextExport
# 	2:10:HeaderFile:textexport.h
# 	2:8:ImplFile:textexport.cpp
# End Section
# Section ComCtrl : {CDE865C4-6B25-4604-8813-F0A65E51F1C8}
# 	2:5:Class:CColorLineTool
# 	2:10:HeaderFile:colorlinetool.h
# 	2:8:ImplFile:colorlinetool.cpp
# End Section
# Section ComCtrl : {62DD8659-F041-11D4-93B1-006008A7EED4}
# 	2:5:Class:CDrawLine
# 	2:10:HeaderFile:drawline.h
# 	2:8:ImplFile:drawline.cpp
# End Section
# Section ComCtrl : {B6C10539-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CClockSeries
# 	2:10:HeaderFile:clockseries.h
# 	2:8:ImplFile:clockseries.cpp
# End Section
# Section ComCtrl : {750EB847-B333-4A73-8AEE-9087F8B98D1E}
# 	2:5:Class:CToolList
# 	2:10:HeaderFile:toollist.h
# 	2:8:ImplFile:toollist.cpp
# End Section
# Section ComCtrl : {B6C104C8-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CShapeSeries
# 	2:10:HeaderFile:shapeseries.h
# 	2:8:ImplFile:shapeseries.cpp
# End Section
# Section ComCtrl : {9CE4E780-4431-4504-948A-797D83C1E310}
# 	2:5:Class:CDragMarksTool
# 	2:10:HeaderFile:dragmarkstool.h
# 	2:8:ImplFile:dragmarkstool.cpp
# End Section
# Section ComCtrl : {B6C10509-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CSeriesMarksPositions
# 	2:10:HeaderFile:seriesmarkspositions.h
# 	2:8:ImplFile:seriesmarkspositions.cpp
# End Section
# Section ComCtrl : {7791BA42-E020-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CButton1
# 	2:10:HeaderFile:button.h
# 	2:8:ImplFile:button.cpp
# End Section
# Section ComCtrl : {B86AE373-50DC-4AE9-8872-8E3F9FC21A4E}
# 	2:5:Class:CMACDFunction
# 	2:10:HeaderFile:macdfunction.h
# 	2:8:ImplFile:macdfunction.cpp
# End Section
# Section ComCtrl : {3752717C-15C0-4C15-9532-C9C371388028}
# 	2:5:Class:CADXFunction
# 	2:10:HeaderFile:adxfunction.h
# 	2:8:ImplFile:adxfunction.cpp
# End Section
# Section ComCtrl : {B6C1050B-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CPolarSeries
# 	2:10:HeaderFile:polarseries.h
# 	2:8:ImplFile:polarseries.cpp
# End Section
# Section ComCtrl : {B6C104DF-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CErrorBarSeries
# 	2:10:HeaderFile:errorbarseries.h
# 	2:8:ImplFile:errorbarseries.cpp
# End Section
# Section ComCtrl : {B6C10534-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CTeePoint3D
# 	2:10:HeaderFile:teepoint3d.h
# 	2:8:ImplFile:teepoint3d.cpp
# End Section
# Section ComCtrl : {70C80BD0-D36A-46C9-A9D6-AE8687CA0EA5}
# 	2:5:Class:CHistogramSeries
# 	2:10:HeaderFile:histogramseries.h
# 	2:8:ImplFile:histogramseries.cpp
# End Section
# Section ComCtrl : {B6C104A3-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CScroll
# 	2:10:HeaderFile:scroll.h
# 	2:8:ImplFile:scroll.cpp
# End Section
# Section ComCtrl : {449C6526-C2F8-47EE-8386-32D20B488B8B}
# 	2:5:Class:CCursorTool
# 	2:10:HeaderFile:cursortool.h
# 	2:8:ImplFile:cursortool.cpp
# End Section
# Section ComCtrl : {B6C104E8-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CCurveFittingFunction
# 	2:10:HeaderFile:curvefittingfunction.h
# 	2:8:ImplFile:curvefittingfunction.cpp
# End Section
# Section ComCtrl : {B6C104BF-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CAreaSeries
# 	2:10:HeaderFile:areaseries.h
# 	2:8:ImplFile:areaseries.cpp
# End Section
# Section ComCtrl : {B6C10504-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CBezierSeries
# 	2:10:HeaderFile:bezierseries.h
# 	2:8:ImplFile:bezierseries.cpp
# End Section
# Section ComCtrl : {B6C104AF-FB89-11D4-93C9-006008A7EED4}
# 	2:5:Class:CValueList
# 	2:10:HeaderFile:valuelist.h
# 	2:8:ImplFile:valuelist.cpp
# End Section
