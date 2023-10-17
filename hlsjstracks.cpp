#include "hlsjstracks.h"

HlsJsTracks::HlsJsTracks()
{

}
class HlsJsTracks extends Notifications {
  get isDestroyed() {
    return this._isDestroyed;
  }
  get audioTracks() {
    return this._audioTracks;
  }
  get textTracks() {
    return this._textTracks;
  }
  set audioTrack (e) {
    this.session && e && void 0 !== e.id && (this.session.audioSelectedPersistentID = e.id);
  }
  set textTrack (e) {
    var n;
    this.session.subtitleSelectedPersistentID = null !== (n = null == e ? void 0 : e.id) && void 0 !== n ? n : -1;
  }
  selectForcedTrack() {
    const {session: e} = this;
    if (!(null == e ? void 0 : e.audioTracks)) return;
    const n = e.audioTracks.filter(n => n.persistentID === e.audioSelectedPersistentID), d = n && n.length && n[0];
    if (!d) return;
    const h = e.subtitleMediaOptions.filter(e => 0 === e.MediaSelectionOptionsDisplaysNonForcedSubtitles && e.MediaSelectionOptionsExtendedLanguageTag === d.lang), p = null == h ? void 0 : h[0];
    let y;
    return p ? (Ct.debug("hlsjsTracks: found forced track for " + p.MediaSelectionOptionsExtendedLanguageTag), e.subtitleSelectedPersistentID = p.MediaSelectionOptionsPersistentID, y = this.normalizeTextTrack(p)) : e.subtitleSelectedPersistentID = -1, y;
  }
  audioTracksUpdated(e, n) {
    const d = (n && n.audioMediaSelectionGroup && n.audioMediaSelectionGroup.MediaSelectionGroupOptions || []).map(this.normalizeAudioTrack, this);
    this._audioTracks = d, this.dispatchEvent(Lo, d);
  }
  handleAudioTrackSwitched() {
    this.dispatchEvent(xo, {selectedId: this.session.audioSelectedPersistentID});
  }
  handleInlineStylesParsed(e, n) {
    this.dispatchEvent(No, n);
  }
  handleManifestLoaded(e, n) {
    this.audioTracksUpdated(e, n), this.subtitleTracksUpdated(e, n);
  }
  handleSessionDataComplete(e, n) {
    var d;
    null == n || null === (d = n.itemList) || void 0 === d || d.forEach(e => {
      "_hls.localized-rendition-names" === e["DATA-ID"] && ("string" == typeof e.VALUE ? this._localizedRenditionNames = JSON.parse(Se(Pe(e.VALUE))) : this._localizedRenditionNames = e.VALUE, this._audioTracks.forEach(e => {
        var n;
        const d = null === (n = this._localizedRenditionNames) || void 0 === n ? void 0 : n[e.label];
        d && (e.localizedRenditionNames = d);
      }), this.dispatchEvent(Lo, this._audioTracks));
    });
  }
  handleSubtitleTrackSwitch(e, n) {
    this.dispatchEvent(jo, n);
  }
  subtitleTracksUpdated(e, n) {
    const d = n && n.subtitleMediaSelectionGroup && n.subtitleMediaSelectionGroup.MediaSelectionGroupOptions || [], h = [];
    d.forEach(e => {
      0 !== e.MediaSelectionOptionsDisplaysNonForcedSubtitles && h.push(this.normalizeTextTrack(e));
    }), this._textTracks = h, this.dispatchEvent(Uo, h);
  }
  normalizeAudioTrack(e) {
    const n = e.MediaSelectionOptionsTaggedMediaCharacteristics, d = (null != n ? n : []).includes("public.accessibility.describes-video") ? "description" : "main";
    return _objectSpreadProps$3(_objectSpread$6({}, this.normalizeSelectionOption(e)), {enabled: false, kind: d, characteristics: n});
  }
  normalizeTextTrack(e) {
    var n;
    let d;
    return d = (null === (n = e.MediaSelectionOptionsTaggedMediaCharacteristics) || void 0 === n ? void 0 : n.includes("public.accessibility.describes-music-and-sound")) || "clcp" === e.MediaSelectionOptionsMediaType ? "captions" : "subtitles", _objectSpreadProps$3(_objectSpread$6({}, this.normalizeSelectionOption(e)), {mode: "disabled", kind: d});
  }
  normalizeSelectionOption(e) {
    return {id: e.MediaSelectionOptionsPersistentID, label: e.MediaSelectionOptionsName, language: e.MediaSelectionOptionsExtendedLanguageTag};
  }
  destroy() {
    this._isDestroyed = true;
    const {MANIFEST_LOADED: e, AUDIO_TRACK_SWITCHED: n, SUBTITLE_TRACK_SWITCH: d, INLINE_STYLES_PARSED: h} = window.Hls.Events;
    this.session.off(e, this.handleManifestLoaded), this.session.off(n, this.handleAudioTrackSwitched), this.session.off(d, this.handleSubtitleTrackSwitch), this.session.off(h, this.handleInlineStylesParsed);
  }
  constructor(e) {
    super([xo, Lo, No, jo, Uo]), this.session = e, this._audioTracks = [], this._textTracks = [], this._isDestroyed = false;
    const {MANIFEST_LOADED: n, AUDIO_TRACK_SWITCHED: d, SUBTITLE_TRACK_SWITCH: h, INLINE_STYLES_PARSED: p, SESSION_DATA_COMPLETE: y} = window.Hls.Events;
    this.session.on(n, this.handleManifestLoaded), this.session.on(d, this.handleAudioTrackSwitched), this.session.on(h, this.handleSubtitleTrackSwitch), this.session.on(p, this.handleInlineStylesParsed), this.session.on(y, this.handleSessionDataComplete);
  }
}
