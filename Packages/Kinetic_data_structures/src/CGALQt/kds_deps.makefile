KDS_Qt_widget_2_core$(OBJ_EXT): KDS_Qt_widget_2_core.moc

KDS_Qt_core$(OBJ_EXT): KDS_Qt_core.moc

KDS_Qt_timer$(OBJ_EXT): KDS_Qt_timer.moc

KDS_Qt_window_2$(OBJ_EXT): KDS_Qt_window_2.moc

#KDS_Qt_examiner_viewer$(OBJ_EXT): KDS_Qt_examiner_viewer.moc

KDS_pixmaps$(OBJ_EXT): KDS_*.xpm


KDS_%.moc: ../../include/CGAL/KDS/IO/internal/KDS_%.h
	$(QT_MOC) $< > $@
