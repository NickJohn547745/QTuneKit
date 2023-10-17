#include "texttrackmanager.h"

TextTrackManager::TextTrackManager()
{

}
class TextTrackManager {
  get isDestroyed() {
    return this._isDestroyed;
  }
  get currentTrack() {
    return this.tracks.find(e => "showing" === e.mode);
  }
  set currentTrack (e) {
    if (!e) return;
    let n;
    this.trackPersistence.setPersistedTrack(e), this.extensionTracks ? (Ct.debug("MEDIA_TRACK Setting track on extension " + e.label), "Off" === e.label ? (this.clearCurrentlyPlayingTrack(), n = this.extensionTracks.selectForcedTrack(), void 0 === n && this.onExtensionTextTrackSwitched({track: e})) : this.extensionTracks.textTrack = e) : (Ct.debug("MEDIA_TRACK Setting track on element " + e.label), this._tracks.forEach(n => {
      n !== e && "showing" === n.mode && (n.mode = "disabled");
    }), e && (Ct.debug("MEDIA_TRACK setting track mode to showing for " + e.label), this.isTrackOff(e) ? (this._tracks[0].mode = "showing", n = this.selectNativeForcedTrack(this.mediaElement.audioTracks)) : e.mode = "showing")), this.dispatcher.publish(dr.forcedTextTrackChanged, n);
  }
  get tracks() {
    return this._tracks;
  }
  destroy() {
    if (this._isDestroyed = true, this.clearCurrentlyPlayingTrack(), this.extensionTracks) {
      const e = this.extensionTracks;
      e.removeEventListener(sa, this.onExtensionTextTracksAdded), e.removeEventListener(aa, this.onExtensionTextTrackSwitched), e.removeEventListener(oa, this.onExtensionInlineStylesParsed);
    } else this.mediaElement.textTracks.removeEventListener("addtrack", this.onTextTrackAdded), this.mediaElement.textTracks.removeEventListener("change", this.onTextTrackChanged), this.mediaElement.textTracks.removeEventListener("removetrack", this.onTextTrackRemoved), this.mediaElement.removeEventListener("playing", this.onPlayStart);
    this.dispatcher.unsubscribe(ea, this.onAudioTrackAddedOrChanged), this.dispatcher.unsubscribe(Zi, this.onAudioTrackAddedOrChanged);
  }
  restoreSelectedTrack() {
    return restoreSelectedTrack(this.trackPersistence, this);
  }
  onExtensionInlineStylesParsed(e) {
    Ct.debug("MEDIA_TRACK Extension inline styles parsed", e), this.renderer.setStyles(e.styles);
  }
  onExtensionTextTracksAdded(e) {
    Ct.debug("MEDIA_TRACK Extension text tracks updated " + JSON.stringify(e)), this._tracks.push(...e), this.restoreSelectedTrack(), this.dispatcher.publish(ra, e);
  }
  onExtensionTextTrackSwitched(e) {
    Ct.debug("MEDIA_TRACKS Extension text track switched " + e), this.handleVTT(e);
    const n = e.track;
    if (this._tracks) {
      const preserveSelectedTrack = d => {
        e.track ? n.forced && "Off" === d.label || "Off" === n.label && "Off" === d.label ? d.mode = "showing" : d.mode = e.track.persistentID === d.id ? "showing" : "disabled" : d.mode = "Off" === d.label ? "showing" : "disabled";
      };
      this._tracks.forEach(preserveSelectedTrack);
    }
    this.dispatcher.publish(na, e);
  }
  handleVTT(e) {
    const n = e && e.track && e.track.id;
    if (void 0 !== n && n >= 0) {
      const e = this.filterSelectableTextTracks(this.mediaElement.textTracks)[n];
      this.onNativeTrackChange(e);
    } else this.clearCurrentlyPlayingTrack();
  }
  onAudioTrackAddedOrChanged(e, n) {
    if (Ct.debug("MEDIA_TRACKS text track manager detects audio track change"), this.shouldForceSubtitle()) if (this.extensionTracks) {
      Ct.debug("MEDIA_TRACKS selecting forced text track via extension");
      const e = this.extensionTracks.selectForcedTrack();
      e ? this.dispatcher.publish(ta, e) : this.clearCurrentlyPlayingTrack();
    } else Ct.debug("MEDIA_TRACKS selecting forced text track natively"), this.currentTrack = this._tracks[0];
  }
  onTextTrackAdded(e) {
    this._tracks.push(e.track), this.dispatcher.publish(ra, e);
  }
  onPlayStart() {
    this.restoreSelectedTrack();
  }
  onTextTrackRemoved(e) {
    this.dispatcher.publish(ia, e);
  }
  onTextTrackChanged(e) {
    const n = this.findNativeSelectedTextTrack();
    let d = this.trackPersistence.getPersistedTrack();
    if (d || (d = this._tracks[0]), n && !trackEquals(n, d, this.trackPersistence.fields)) if (this.isTrackOff(d) && "forced" !== n.kind) this.currentTrack = d; else {
      const e = this.findNativeTrack(d);
      e && (this.currentTrack = e);
    } else this.dispatcher.publish(na, e);
  }
  findNativeSelectedTextTrack() {
    for (let e = 0; e < this.mediaElement.textTracks.length; e++) {
      const n = this.mediaElement.textTracks[e];
      if ("showing" === n.mode) return n;
    }
  }
  findNativeTrack(e) {
    for (let n = 0; n < this.mediaElement.textTracks.length; n++) {
      const d = this.mediaElement.textTracks[n];
      if (trackEquals(d, e, this.trackPersistence.fields)) return d;
    }
  }
  selectNativeForcedTrack(e) {
    for (let n = 0; n < e.length; n++) {
      const d = e[n];
      if (d.enabled) {
        const e = this.findNativeForcedTrack(d);
        return e && "showing" !== e.mode && (e.mode = "showing"), e;
      }
    }
  }
  findNativeForcedTrack(e) {
    const n = this.mediaElement.textTracks;
    for (let d = 0; d < n.length; d++) {
      const h = n[d];
      if ("forced" === h.kind && h.language === e.language) return h;
    }
  }
  onNativeTrackChange(e) {
    this.clearCurrentlyPlayingTrack(), this._currentlyPlayingTrack = e, e.addEventListener("cuechange", this.onCueChange);
  }
  clearCurrentlyPlayingTrack() {
    var e;
    void 0 !== this._currentlyPlayingTrack && ("string" == typeof (e = this._currentlyPlayingTrack).id && "removeEventListener" in e) && (this._currentlyPlayingTrack.removeEventListener("cuechange", this.onCueChange), this.renderer.processCues({}), delete this._currentlyPlayingTrack);
  }
  onCueChange(e) {
    const n = e && e.target && e.target.activeCues;
    n && this.renderer.processCues(n);
  }
  filterSelectableTextTracks(e) {
    const n = [];
    for (let d = 0; d < e.length; d++) {
      const h = e[d];
      ("captions" === h.kind || "subtitles" === h.kind || "metadata" === h.kind && h.customTextTrackCueRenderer) && n.push(h);
    }
    return n;
  }
  shouldForceSubtitle() {
    Ct.debug("MEDIA_TRACKS Determining whether to select forced text track");
    const e = this.trackPersistence.getPersistedTrack();
    return !e || this.isTrackOff(e);
  }
  isTrackOff(e) {
    return "Off" === e.label || "Auto" === e.label;
  }
  constructor(e, n, d) {
    this.mediaElement = e, this.dispatcher = n, this.extensionTracks = d, this._tracks = [], this.trackPersistence = new TrackPersistence("mk-text-track", ["label", "language", "kind"]), this._isDestroyed = false;
    const h = this.trackPersistence.getPersistedTrack();
    if (this._tracks.push({id: -2, label: "Off", language: "", kind: "subtitles", mode: !h || this.isTrackOff(h) ? "showing" : "disabled"}), this.extensionTracks) {
      Ct.debug("MEDIA_TRACK Initializing text track manager for HLS.js track events");
      const n = e.parentElement;
      this.renderer = new Xi(window, n, false), this.renderer.setStyles({"::cue": {fontSize: "calc(1vw + 1em)"}}), this.onExtensionTextTracksAdded = this.onExtensionTextTracksAdded.bind(this), this.onExtensionTextTrackSwitched = this.onExtensionTextTrackSwitched.bind(this), this.onExtensionInlineStylesParsed = this.onExtensionInlineStylesParsed.bind(this), this.onCueChange = this.onCueChange.bind(this);
      const d = this.extensionTracks;
      d.addEventListener(sa, this.onExtensionTextTracksAdded), d.addEventListener(aa, this.onExtensionTextTrackSwitched), d.addEventListener(oa, this.onExtensionInlineStylesParsed);
    } else Ct.debug("MEDIA_TRACK Initializing text track manager for native track events"), this.onTextTrackAdded = this.onTextTrackAdded.bind(this), this.onTextTrackChanged = this.onTextTrackChanged.bind(this), this.onTextTrackRemoved = this.onTextTrackRemoved.bind(this), this.onPlayStart = this.onPlayStart.bind(this), e.textTracks.addEventListener("addtrack", this.onTextTrackAdded), e.textTracks.addEventListener("change", this.onTextTrackChanged), e.textTracks.addEventListener("removetrack", this.onTextTrackRemoved), e.addEventListener("playing", this.onPlayStart);
    this.onAudioTrackAddedOrChanged = debounce(this.onAudioTrackAddedOrChanged.bind(this)), n.subscribe(ea, this.onAudioTrackAddedOrChanged), n.subscribe(Zi, this.onAudioTrackAddedOrChanged);
  }
}
