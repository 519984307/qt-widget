contains(DEFINES, examples_full) {
FORMS   += $$PWD/frmexamplesfull.ui
HEADERS += $$PWD/frmexamplesfull.h
SOURCES += $$PWD/frmexamplesfull.cpp
} else {
FORMS   += $$PWD/frmexamplessimple.ui
HEADERS += $$PWD/frmexamplessimple.h
SOURCES += $$PWD/frmexamplessimple.cpp
}
