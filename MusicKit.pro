QT -= gui
QT += network concurrent

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api.cpp \
    apiservicemanager.cpp \
    apisession.cpp \
    audioplayer.cpp \
    audiotrackmanager.cpp \
    authbridgeapp.cpp \
    autoplaytrackloader.cpp \
    basemodifiablequeue.cpp \
    basemp4box.cpp \
    baseplayer.cpp \
    baserepeatable.cpp \
    baseseekable.cpp \
    baseshuffler.cpp \
    bitratecalculator.cpp \
    booleandevflag.cpp \
    browser.cpp \
    byterangesegment.cpp \
    callbackhandler.cpp \
    capabilities.cpp \
    continuousplaybackcontroller.cpp \
    continuoussegment.cpp \
    datarecord.cpp \
    datastore.cpp \
    developertoken.cpp \
    dispatch.cpp \
    emsg.cpp \
    encryptedsession.cpp \
    error.cpp \
    factory.cpp \
    fairplayencryptedsession.cpp \
    fullscreen.cpp \
    genericstorage.cpp \
    hlsjspreviewimageloader.cpp \
    hlsjstracks.cpp \
    hlsjsvideoplayer.cpp \
    id3.cpp \
    jsondevflag.cpp \
    keysession.cpp \
    license.cpp \
    localdatastore.cpp \
    localstoragedevflag.cpp \
    logger.cpp \
    lyricsplayactivity.cpp \
    lyricstracker.cpp \
    manifest.cpp \
    mediaapiservice.cpp \
    mediaapiv3.cpp \
    mediaextension.cpp \
    mediaextensionstub.cpp \
    mediaitem.cpp \
    mediaitemplayback.cpp \
    mediasessionmanager.cpp \
    mkdialog.cpp \
    mkerror.cpp \
    mkinstance.cpp \
    mkutils.cpp \
    modifiablequeue.cpp \
    mpafstatemachine.cpp \
    mpaftracker.cpp \
    msebuffer.cpp \
    msession.cpp \
    musickit.cpp \
    musickitinstance.cpp \
    nativesafarivideoplayer.cpp \
    networkcache.cpp \
    notifications.cpp \
    parserutility.cpp \
    parsingerror.cpp \
    percentagewatcher.cpp \
    playactivity.cpp \
    playactivitybase.cpp \
    playactivitybatchablesender.cpp \
    playactivitysender.cpp \
    playactivityservice.cpp \
    playbackcontroller.cpp \
    playbackmonitor.cpp \
    playerseeker.cpp \
    playerstub.cpp \
    preloader.cpp \
    preloadingencryptedsession.cpp \
    psshbox.cpp \
    pubsub.cpp \
    queue.cpp \
    queueitem.cpp \
    repeatable.cpp \
    rollmonitor.cpp \
    rtcstreamingtracker.cpp \
    seekable.cpp \
    segmentlist.cpp \
    segmentprocessor.cpp \
    serialplaybackcontroller.cpp \
    servicesetupview.cpp \
    settings.cpp \
    shuffler.cpp \
    skipavailable.cpp \
    spanwatcher.cpp \
    statelessplayactivity.cpp \
    stationtrackloader.cpp \
    store.cpp \
    storekit.cpp \
    stringdevflag.cpp \
    tencbox.cpp \
    texttrackmanager.cpp \
    timedmetadata.cpp \
    timedmetadatamanager.cpp \
    timedmetadatatracker.cpp \
    timeline.cpp \
    trackmanagerstub.cpp \
    trackpersistence.cpp \
    unsupportedseeker.cpp \
    upnextmonitor.cpp \
    videomediaextension.cpp \
    videoplayer.cpp \
    webkitsession.cpp \
    webvttparser.cpp \
    windowhandlers.cpp

HEADERS += \
    api.h \
    apiservicemanager.h \
    apisession.h \
    audioplayer.h \
    audiotrackmanager.h \
    authbridgeapp.h \
    autoplaytrackloader.h \
    basemodifiablequeue.h \
    basemp4box.h \
    baseplayer.h \
    baserepeatable.h \
    baseseekable.h \
    baseshuffler.h \
    bitratecalculator.h \
    booleandevflag.h \
    browser.h \
    byterangesegment.h \
    callbackhandler.h \
    capabilities.h \
    continuousplaybackcontroller.h \
    continuoussegment.h \
    datarecord.h \
    datastore.h \
    developertoken.h \
    dispatch.h \
    emsg.h \
    encryptedsession.h \
    error.h \
    factory.h \
    fairplayencryptedsession.h \
    fullscreen.h \
    genericstorage.h \
    hlsjspreviewimageloader.h \
    hlsjstracks.h \
    hlsjsvideoplayer.h \
    id3.h \
    jobject.h \
    jsondevflag.h \
    keysession.h \
    license.h \
    localdatastore.h \
    localstoragedevflag.h \
    logger.h \
    lyricsplayactivity.h \
    lyricstracker.h \
    manifest.h \
    mediaapiservice.h \
    mediaapiv3.h \
    mediaextension.h \
    mediaextensionstub.h \
    mediaitem.h \
    mediaitemplayback.h \
    mediasessionmanager.h \
    mkdialog.h \
    mkerror.h \
    mkinstance.h \
    mkutils.h \
    modifiablequeue.h \
    mpafstatemachine.h \
    mpaftracker.h \
    msebuffer.h \
    msession.h \
    musickit.h \
    musickitinstance.h \
    nativesafarivideoplayer.h \
    networkcache.h \
    notifications.h \
    parserutility.h \
    parsingerror.h \
    percentagewatcher.h \
    playactivity.h \
    playactivitybase.h \
    playactivitybatchablesender.h \
    playactivitysender.h \
    playactivityservice.h \
    playbackcontroller.h \
    playbackmonitor.h \
    playerseeker.h \
    playerstub.h \
    preloader.h \
    preloadingencryptedsession.h \
    psshbox.h \
    pubsub.h \
    queue.h \
    queueitem.h \
    repeatable.h \
    rollmonitor.h \
    rtcstreamingtracker.h \
    seekable.h \
    segmentlist.h \
    segmentprocessor.h \
    serialplaybackcontroller.h \
    servicesetupview.h \
    settings.h \
    shuffler.h \
    skipavailable.h \
    spanwatcher.h \
    statelessplayactivity.h \
    stationtrackloader.h \
    store.h \
    storekit.h \
    stringdevflag.h \
    tencbox.h \
    texttrackmanager.h \
    timedmetadata.h \
    timedmetadatamanager.h \
    timedmetadatatracker.h \
    timeline.h \
    trackmanagerstub.h \
    trackpersistence.h \
    unsupportedseeker.h \
    upnextmonitor.h \
    videomediaextension.h \
    videoplayer.h \
    webkitsession.h \
    webvttparser.h \
    windowhandlers.h

TRANSLATIONS += \
    MusicKit_en_US.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
