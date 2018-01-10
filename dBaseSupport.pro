#------------------------------------------------------------------------
# dBase4Linux 1.0
# RDP - Rapid Database Programming
#
# (c) 2015-2018 Jens Kallup
#------------------------------------------------------------------------
PWD=$$system(pwd)

include("/home/jens/qtcreator/4.5.0/src/qtcreatorplugin.pri")  # FIXME
TOPDIR=.
SRCDIR=$${TOPDIR}

LIBLDR=/home/jens/qtcreator/4.5.0/lib/qtcreator  # FIXME

UI_DIR =$${PWD}/.uic
MOC_DIR=$${PWD}/.moc
RCC_DIR=$${PWD}/.res
OBJECTS_DIR=$${PWD}/.obj

DEFINES += BUILDTIME=\\\"$$system(date '+%H:%M:%S')\\\"
DEFINES += BUILDDATE=\\\"$$system(date '+%Y-%m-%d')\\\"

DEFINES += DBASE_LIBRARY

CONFIG  += plugin debug
TARGET   = $$PWD/dbasesupportplugin
TEMPLATE = lib

INCLUDEPATH += $$PWD

HEADERS += \
    $${SRCDIR}/dbasesupport.h \
    $${SRCDIR}/editor/dbaseeditorfactory.h \
    $${SRCDIR}/editor/dbaseindenter.h \
    $${SRCDIR}/editor/dbasehighlighter.h \
    $${SRCDIR}/project/dbaseproject.h \
    $${SRCDIR}/project/dbaseprojectnode.h \
    $${SRCDIR}/project/dbaserunconfigurationfactory.h \
    $${SRCDIR}/project/dbaserunconfiguration.h \
    $${SRCDIR}/project/dbasetoolchain.h \
    $${SRCDIR}/project/dbasetoolchainfactory.h \
    $${SRCDIR}/project/dbasebuildconfiguration.h \
    $${SRCDIR}/project/dbasebuildconfigurationfactory.h \
    $${SRCDIR}/project/dbasebuildconfigurationwidget.h \
    $${SRCDIR}/project/dbasecompilerbuildstep.h \
    $${SRCDIR}/project/dbasecompilerbuildstepconfigwidget.h \
    $${SRCDIR}/project/dbasecompilerbuildstepfactory.h \
    $${SRCDIR}/project/dbasecompilercleanstep.h \
    $${SRCDIR}/project/dbasecompilercleanstepconfigwidget.h \
    $${SRCDIR}/project/dbasecompilercleanstepfactory.h \
    $${SRCDIR}/project/dbaseproject.h \
    $${SRCDIR}/project/dbaseprojectnode.h \
    $${SRCDIR}/project/dbaserunconfiguration.h \
    $${SRCDIR}/project/dbaserunconfigurationfactory.h \
    $${SRCDIR}/project/dbaserunconfigurationwidget.h \
    $${SRCDIR}/project/dbasetoolchain.h \
    $${SRCDIR}/project/dbasetoolchainfactory.h \
    $${SRCDIR}/database/dbsql.h \
    $${SRCDIR}/database/popupmenu.h \
    $${SRCDIR}/plugins/dbaseplugin.h \
    $${SRCDIR}/plugins/dbasepluginconstants.h \
    $${SRCDIR}/plugins/dbsqlplugin.h \
    $${SRCDIR}/plugins/popupmenuplugin.h
    
SOURCES += \
    $${SRCDIR}/dbasesupport.cc \
    $${SRCDIR}/editor/dbaseeditorfactory.cc \
    $${SRCDIR}/editor/editorindent.cc \
    $${SRCDIR}/editor/dbasehighlighter.cc \
    $${SRCDIR}/project/dbaseproject.cc \
    $${SRCDIR}/project/dbaseprojectnode.cc \
    $${SRCDIR}/project/dbaserunconfigurationfactory.cc \
    $${SRCDIR}/project/dbaserunconfiguration.cc \
    $${SRCDIR}/project/dbasetoolchain.cc \
    $${SRCDIR}/project/dbasetoolchainfactory.cc \
    $${SRCDIR}/project/dbasebuildconfiguration.cc \
    $${SRCDIR}/project/dbasebuildconfigurationfactory.cc \
    $${SRCDIR}/project/dbasebuildconfigurationwidget.cc \
    $${SRCDIR}/project/dbasecompilerbuildstep.cc \
    $${SRCDIR}/project/dbasecompilerbuildstepconfigwidget.cc \
    $${SRCDIR}/project/dbasecompilerbuildstepfactory.cc \
    $${SRCDIR}/project/dbasecompilercleanstep.cc \
    $${SRCDIR}/project/dbasecompilercleanstepconfigwidget.cc \
    $${SRCDIR}/project/dbasecompilercleanstepfactory.cc \
    $${SRCDIR}/project/dbaseproject.cc \
    $${SRCDIR}/project/dbaseprojectnode.cc \
    $${SRCDIR}/project/dbaserunconfiguration.cc \
    $${SRCDIR}/project/dbaserunconfigurationfactory.cc \
    $${SRCDIR}/project/dbaserunconfigurationwidget.cc \
    $${SRCDIR}/project/dbasetoolchain.cc \
    $${SRCDIR}/project/dbasetoolchainfactory.cc \
    $${SRCDIR}/database/dbsql.cc \
    $${SRCDIR}/database/popupmenu.cc \
    $${SRCDIR}/plugins/dbaseplugin.cc \
    $${SRCDIR}/plugins/dbsqlplugin.cc \
    $${SRCDIR}/plugins/popupmenuplugin.cc
    
RESOURCES   = icons/icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

DISTFILES += \
    dBaseSupport_dependencies.pri \
    dbase.json \

FORMS += \
    project/dbasecompilerbuildstepconfigwidget.ui \
    project/dbasecompilercleanstepconfigwidget.ui

LIBS += -L. -L$${LIBLDR}/plugins -lCore
LIBS += -L. -L$${LIBLDR}/plugins -lTextEditor
LIBS += -L. -L$${LIBLDR} -lProjectExplorer
LIBS += -L. -L$${LIBLDR} -lAggregation
LIBS += -L. -L$${LIBLDR} -lExtensionSystem
LIBS += -L. -L$${LIBLDR} -lQtcSsh
LIBS += -L. -L$${LIBLDR} -lUtils
