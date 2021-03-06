# This include file makes generation and installation of .qm files
# from .ts files and updating .ts files from the sources easier.

# get around lack of sleep on Windows:
unix:SLEEP = sleep 1
else:SLEEP = ping -n 5 localhost > NUL
# null device:
unix:NULL = /dev/null
else:NULL = NUL

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

defineReplace(targetPath) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}
isEmpty(LRELEASE_OPTIONS) {
    LRELEASE_OPTIONS = -idbased
    # add “-markuntranslated '!!\ '” if available (needs new Qt 4.6):
    out = $$system($$targetPath($$[QT_INSTALL_BINS]/lrelease) -help)
    # the second parameter of contains can be a regexp!
    contains(out, .*markuntranslated.*) {
    LRELEASE_OPTIONS += -markuntranslated '!!\\ '
    }
}
isEmpty(LUPDATE_OPTIONS) {
    LUPDATE_OPTIONS = -locations absolute -no-ui-lines -no-sort
}
LRELEASE = $$targetPath($$[QT_INSTALL_BINS]/lrelease) $$LRELEASE_OPTIONS
LUPDATE = $$targetPath($$[QT_INSTALL_BINS]/lupdate) $$LUPDATE_OPTIONS

TRANSLATIONS = $$prependAll(LANGUAGES, $$TRANSLATIONDIR/$${CATALOGNAME}_,.ts)

isEqual(TEMPLATE_PREFIX, vc):vcproj=1
isEmpty(vcproj) {
    QMAKE_LINK = @: IGNORE THIS LINE
    OBJECTS_DIR =
    win32:CONFIG -= embed_manifest_exe
} else {
    CONFIG += console
    PHONY_DEPS = .
    phony_src.input = PHONY_DEPS
    phony_src.output = phony.c
    phony_src.variable_out = GENERATED_SOURCES
    phony_src.commands = echo int main() { return 0; } > phony.c
    phony_src.name = CREATE phony.c
    phony_src.CONFIG += combine
    QMAKE_EXTRA_COMPILERS += phony_src
}


!isEqual(DISABLE_QTTRID_ENGINEERING_ENGLISH, "yes") {
    ENGINEERING_ENGLISH = $$OUT_PWD/$${CATALOGNAME}.ts
    # updating the engineering English .ts file should be done *always*
    # because it is fully auto-generated, no manual editing is needed:

    DUMMY_DEP = $$OUT_PWD/dummy-dependency-this-file-will-never-be-created
    updateeets.input = DUMMY_DEP
    updateeets.output = $$ENGINEERING_ENGLISH
    !isEmpty(vcproj):updateeets.variable_out = GENERATED_SOURCES
    updateeets.commands = $$LUPDATE "$$SOURCEDIR" -ts "$$ENGINEERING_ENGLISH"
    updateeets.name = LUPDATE $$ENGINEERING_ENGLISH
    updateeets.CONFIG += no_link target_predeps
    QMAKE_EXTRA_COMPILERS += updateeets

    FORCED_DEP = .
    dummy.input = FORCED_DEP
    dummy.output = $$DUMMY_DEP
    !isEmpty(vcproj):dummy.variable_out = GENERATED_SOURCES
    # we do not really create $$DUMMY_DEP here, make does not check the
    # output of the build steps, it assumes that the build command either
    # fails or that the output is created:
    dummy.commands = echo > $$NULL
    dummy.CONFIG += no_link target_predeps
    QMAKE_EXTRA_COMPILERS += dummy
}

# other .ts files besides the engineering English one should only be updated
# on request, i.e. only when calling “make updatets” manually:
updatets.commands = $$LUPDATE "$$SOURCEDIR" -ts "$$TRANSLATIONS"
updatets.target = updatets
QMAKE_EXTRA_TARGETS += updatets

updateqm.input = TRANSLATIONS
!isEqual(DISABLE_QTTRID_ENGINEERING_ENGLISH, "yes") {
    updateqm.input += ENGINEERING_ENGLISH
}
updateqm.output = $$OUT_PWD/${QMAKE_FILE_BASE}.qm
updateqm.commands = $$LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
updateqm.name = LRELEASE ${QMAKE_FILE_IN}
updateqm.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += updateqm

!isEmpty(TRANSLATION_INSTALLDIR) {
    qmfiles.files = $$prependAll(LANGUAGES, $$OUT_PWD/$${CATALOGNAME}_,.qm)
    !isEqual(DISABLE_QTTRID_ENGINEERING_ENGLISH, "yes") {
        qmfiles.files += $$OUT_PWD/$${CATALOGNAME}.qm
    }
    qmfiles.CONFIG += no_check_exist
    qmfiles.path = $$TRANSLATION_INSTALLDIR
    INSTALLS += qmfiles
}

