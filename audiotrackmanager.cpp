#include "audiotrackmanager.h"

AudioTrackManager::AudioTrackManager()
{

}
class AudioTrackManager {
  get isDestroyed() {
    return this._isDestroyed;
  }
  get currentTrack() {
    return this.tracks.find(e => e.enabled);
  }
  set currentTrack (e) {
    e && (Ct.debug("MEDIA_TRACK Setting audio track " + e.label), this.extensionTracks ? (Ct.debug(`MEDIA_TRACK Setting track on extension ${e.id}-${e.label}`), this.extensionTracks.audioTrack = e) : (Ct.debug("MEDIA_TRACK disabling all audio tracks"), Array.from(this.mediaElement.audioTracks).forEach(n => {
      n !== e && (n.enabled = false);
    }), Ct.debug("MEDIA_TRACK enabling", e), e.enabled = true), function (e) {
      return void 0 !== e.characteristics && e.characteristics.includes("com.apple.amp.appletv.home-team-radio");
    }(e) || function (e) {
      return void 0 !== e.characteristics && e.characteristics.includes("com.apple.amp.appletv.away-team-radio");
    }(e) || this.trackPersistence.setPersistedTrack(e));
  }
  get tracks() {
    return this.extensionTracks ? this._extensionTracks || this.extensionTracks.audioTracks || [] : Array.from(this.mediaElement.audioTracks);
  }
  destroy() {
    if (this._isDestroyed = true, this.extensionTracks) {
      const e = this.extensionTracks;
      e.removeEventListener(Fi, this.onExtensionAudioTracksUpdated), e.removeEventListener(Bi, this.onExtensionAudioTrackSwitched);
    } else {
      if (!this.mediaElement.audioTracks) return;
      this.mediaElement.audioTracks.removeEventListener("addtrack", this.onAudioTrackAdded), this.mediaElement.audioTracks.removeEventListener("change", this.onAudioTrackChanged), this.mediaElement.audioTracks.removeEventListener("removetrack", this.onAudioTrackRemoved);
    }
  }
  restoreSelectedTrack() {
    return restoreSelectedTrack(this.trackPersistence, this);
  }
  onExtensionAudioTracksUpdated(e) {
    Ct.debug("MEDIA_TRACK Extension audio tracks updated " + JSON.stringify(e)), this._extensionTracks = e, this.restoreSelectedTrack(), this.dispatcher.publish(Ui, e);
  }
  onExtensionAudioTrackSwitched(e) {
    if (Ct.debug("MEDIA_TRACK Extension audio track switched " + JSON.stringify(e)), this._extensionTracks) {
      const preserveSelectedTrack = n => {
        n.enabled = e.selectedId === n.id;
      };
      this._extensionTracks.forEach(preserveSelectedTrack);
    }
    this.dispatcher.publish($i, e);
  }
  onAudioTrackAdded(e) {
    !function (e, n, d) {
      const h = n.getPersistedTrack();
      h && trackEquals(e, h, n.fields) && (Ct.debug("MEDIA_TRACK onTrackAdded with track that matches persisted track " + e.label), d.currentTrack = e);
    }(e.track, this.trackPersistence, this), this.dispatcher.publish(Ui, e);
  }
  onAudioTrackChanged(e) {
    this.dispatcher.publish($i, e);
  }
  onAudioTrackRemoved(e) {
    this.dispatcher.publish(Gi, e);
  }
  constructor(e, n, d) {
    if (this.mediaElement = e, this.dispatcher = n, this.extensionTracks = d, this._extensionTracks = [], this.trackPersistence = new TrackPersistence("mk-audio-track", ["label", "language", "kind"]), this._isDestroyed = false, this.extensionTracks) {
      Ct.debug("MEDIA_TRACK Initializing audio track manager for hls track events"), this.onExtensionAudioTracksUpdated = this.onExtensionAudioTracksUpdated.bind(this), this.onExtensionAudioTrackSwitched = this.onExtensionAudioTrackSwitched.bind(this);
      const e = this.extensionTracks;
      e.addEventListener(Fi, this.onExtensionAudioTracksUpdated), e.addEventListener(Bi, this.onExtensionAudioTrackSwitched);
    } else {
      if (!e.audioTracks) return;
      Ct.debug("MEDIA_TRACK Initializing audio track manager for native track events"), this.onAudioTrackAdded = this.onAudioTrackAdded.bind(this), this.onAudioTrackChanged = this.onAudioTrackChanged.bind(this), this.onAudioTrackRemoved = this.onAudioTrackRemoved.bind(this), e.audioTracks.addEventListener("addtrack", this.onAudioTrackAdded), e.audioTracks.addEventListener("change", this.onAudioTrackChanged), e.audioTracks.addEventListener("removetrack", this.onAudioTrackRemoved);
    }
  }
}
