set(uti_files_Src_Files
    ${UTI_FILES_DIR}/CPP_MapCmd.cpp
    ${UTI_FILES_DIR}/CPP_BatchFDC.cpp
    ${UTI_FILES_DIR}/CPP_MyRename.cpp
    ${UTI_FILES_DIR}/CPP_cod.cpp
    ${UTI_FILES_DIR}/CPP_GGP_txt2Xml.cpp
    ${UTI_FILES_DIR}/CPP_Ori_txt2Xml.cpp
    ${UTI_FILES_DIR}/CPP_TestKeys.cpp
    ${UTI_FILES_DIR}/CPP_TestMTD.cpp
    ${UTI_FILES_DIR}/CPP_TestCmds.cpp
    ${UTI_FILES_DIR}/CPP_Apero2PMVS.cpp
    ${UTI_FILES_DIR}/CPP_GenHeadTifTile.cpp
)

SOURCE_GROUP(uti_files FILES ${uti_files_Src_Files})

set(Elise_Src_Files
	${Elise_Src_Files}
	${uti_files_Src_Files}
)
