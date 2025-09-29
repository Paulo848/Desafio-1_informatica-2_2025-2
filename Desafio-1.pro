TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        codecs_lz78.cpp \
        codecs_rle.cpp \
        crypto_xor_rot.cpp \
        files.cpp \
        main.cpp \
        pipeline_desencriptar_descomprimir.cpp \
        utils.cpp


HEADERS += \
    codecs_lz78.h \
    codecs_rle.h \
    crypto_xor_rot.h \
    files.h \
    pipeline_desencriptar_descomprimir.h \
    utils.h
