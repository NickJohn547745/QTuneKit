#include "playerstub.h"

PlayerStub::PlayerStub()
{

}
class PlayerStub {
  get hasMediaElement() {
    return true;
  }
  get isEngagedInPlayback() {
    return !this.paused;
  }
  get playbackRate() {
    return this._playbackRate;
  }
  set playbackRate (e) {
    this._playbackRate = e, this._dispatcher.publish(dr.playbackRateDidChange, new Event("ratechange"));
  }
  get volume() {
    return this._volume;
  }
  set volume (e) {
    this._volume = e, this._dispatcher.publish(dr.playbackVolumeDidChange, new Event("volumeChange"));
  }
  destroy() {}
  dispatch() {}
  exitFullscreen() {
    return _asyncToGenerator$C(function* () {})();
  }
  loadPreviewImage(e) {
    return _asyncToGenerator$C(function* () {})();
  }
  initialize() {
    return _asyncToGenerator$C(function* () {})();
  }
  isPaused() {
    return this.paused;
  }
  calculateTime(e) {
    return e;
  }
  clearNextManifest() {}
  mute() {}
  newSeeker() {
    return new PlayerSeeker(this);
  }
  pause(e) {
    return _asyncToGenerator$C(function* () {})();
  }
  play() {
    return _asyncToGenerator$C(function* () {})();
  }
  playItemFromEncryptedSource(e, n, d) {
    return _asyncToGenerator$C(function* () {})();
  }
  playItemFromUnencryptedSource(e, n, d) {
    return _asyncToGenerator$C(function* () {})();
  }
  preload() {
    return _asyncToGenerator$C(function* () {})();
  }
  prepareToPlay(e, n, d) {
    return _asyncToGenerator$C(function* () {})();
  }
  seekToTime(e) {
    return _asyncToGenerator$C(function* () {})();
  }
  requestFullscreen() {
    return _asyncToGenerator$C(function* () {})();
  }
  setPlaybackState(e, n) {}
  setPresentationMode(e) {
    return _asyncToGenerator$C(function* () {})();
  }
  showPlaybackTargetPicker() {}
  stop(e) {
    return _asyncToGenerator$C(function* () {})();
  }
  stopMediaAndCleanup() {
    return _asyncToGenerator$C(function* () {})();
  }
  supportsPictureInPicture() {
    return false;
  }
  tsidChanged() {}
  setNextSeamlessItem(e) {
    return _asyncToGenerator$C(function* () {})();
  }
  constructor(n) {
    this.bitrate = e.PlaybackBitrate.STANDARD, this.audioTracks = [], this.currentBufferedProgress = 0, this.currentPlaybackDuration = 0, this.currentPlaybackProgress = 0, this.currentPlaybackTime = 0, this.currentPlaybackTimeRemaining = 0, this.currentPlayingDate = void 0, this.isPlayingAtLiveEdge = false, this.isPlaying = false, this.isPrimaryPlayer = true, this.isReady = false, this.paused = false, this.playbackState = e.PlaybackStates.none, this.playbackTargetAvailable = false, this.playbackTargetIsWireless = false, this.previewOnly = false, this.supportsPreviewImages = false, this.textTracks = [], this.extension = new MediaExtensionStub([]), this.hasAuthorization = true, this.isDestroyed = false, this._volume = 1, this._playbackRate = 1, this._dispatcher = n.services.dispatcher, this.windowHandlers = new WindowHandlers(this);
  }
}
