#include "mediaitem.h"

MediaItem::MediaItem()
{

}

class MediaItem extends Notifications {
  get ageGatePolicy() {
    var e;
    return null === (e = this.defaultPlayable) || void 0 === e ? void 0 : e.ageGatePolicy;
  }
  get albumInfo() {
    const {albumName: e, artistName: n} = this, d = [];
    return n && d.push(n), e && d.push(e), d.join(" - ");
  }
  get albumName() {
    return this.attributes.albumName;
  }
  get artistName() {
    return this.attributes.genreNames && this.attributes.genreNames.indexOf("Classical") > -1 && this.attributes.composerName ? this.attributes.composerName : this.attributes.artistName;
  }
  get artwork() {
    var e, n;
    return null !== (n = this.attributes.artwork) && void 0 !== n ? n : null === (e = this.attributes.images) || void 0 === e ? void 0 : e.coverArt16X9;
  }
  get artworkURL() {
    if (this.artwork && this.artwork.url) return this.artwork.url;
  }
  get assets() {
    return this._assets;
  }
  get canPlay() {
    return this.isPlayable && this.isReady;
  }
  get container() {
    return this._container;
  }
  set container (e) {
    this._container = e;
  }
  get contentRating() {
    return this.attributes.contentRating;
  }
  get context() {
    return this._context;
  }
  set context (e) {
    this._context = e;
  }
  get defaultPlayable() {
    var e;
    return null === (e = this.playables) || void 0 === e ? void 0 : e[0];
  }
  get discNumber() {
    return this.attributes.discNumber;
  }
  get hasContainerArtwork() {
    return this.container && this.container.attributes && this.container.attributes.artwork && this.container.attributes.artwork.url;
  }
  get hasPlaylistContainer() {
    return this.container && "playlists" === this.container.type && this.container.attributes;
  }
  get isEntitledToPlay() {
    const {attributes: e, defaultPlayable: n} = this;
    var d;
    return null !== (d = e.isEntitledToPlay || (null == n ? void 0 : n.isEntitledToPlay)) && void 0 !== d && d;
  }
  get supportsLinearScrubbing() {
    var e, n, d;
    return this.isLinearStream && true === (null === (e = this.defaultPlayable) || void 0 === e || null === (n = e.assets) || void 0 === n || null === (d = n.streamCapability) || void 0 === d ? void 0 : d.supportsLinearScrubbing);
  }
  get isAssetScrubbingDisabled() {
    return !!this.isLinearStream && !this.supportsLinearScrubbing;
  }
  get isLinearStream() {
    return "LiveService" === (null == (e = this) ? void 0 : e.type) || "Event" === (null == e || null === (n = e.defaultPlayable) || void 0 === n ? void 0 : n.type) || "EbsEvent" === (null == e || null === (d = e.defaultPlayable) || void 0 === d ? void 0 : d.type);
    var e, n, d;
  }
  get isLiveRadioStation() {
    return isLive(this) && isStream$1(this);
  }
  get isLiveAudioStation() {
    return isLiveRadioKind(this, "audio");
  }
  get isLiveVideoStation() {
    return isLiveRadioKind(this, "video");
  }
  get isAOD() {
    return isAOD(this);
  }
  get isSong() {
    return "song" === this.type;
  }
  get info() {
    return `${this.title} - ${this.albumInfo}`;
  }
  get isCloudItem() {
    return this.playParams && this.playParams.isLibrary || P(this.id);
  }
  get isCloudUpload() {
    return -1 === this._songId;
  }
  get isExplicitItem() {
    return "explicit" === this.contentRating;
  }
  get isLoading() {
    return this.state === G.loading;
  }
  get isPlayableMediaType() {
    return this.isUTS || -1 !== k.indexOf(this.type);
  }
  get isPlayable() {
    var e;
    return !!this.isPlayableMediaType && (!(!this.isLiveRadioStation && !this.hasOffersHlsUrl) || (this.needsPlayParams ? !!this.playParams : this.isUTS ? this.isEntitledToPlay : !!this.attributes.assetUrl || !!(null === (e = this.attributes.previews) || void 0 === e ? void 0 : e.length)));
  }
  get isPlaying() {
    return this.state === G.playing;
  }
  get isPreparedToPlay() {
    if ("song" === this.type) return !!this._assets && !!this.keyURLs && !!this._songId;
    if (this.isUTS) {
      const e = isStringNotEmpty(this.assetURL), n = !!(this.keyURLs && isStringNotEmpty(this.keyURLs["hls-key-cert-url"]) && isStringNotEmpty(this.keyURLs["hls-key-server-url"]) && isStringNotEmpty(this.keyURLs["widevine-cert-url"]));
      return e && n;
    }
    return !!isStringNotEmpty(this.assetURL) || this.playRawAssetURL && !!isStringNotEmpty(this.attributes.assetUrl);
  }
  get isrc() {
    return this.attributes.isrc;
  }
  get isReady() {
    return this.state === G.ready;
  }
  get isRestricted() {
    return this.state === G.restricted;
  }
  get isUTS() {
    var e;
    return !(!(null === (e = this.defaultPlayable) || void 0 === e ? void 0 : e.type) || !O.includes(this.defaultPlayable.type));
  }
  get isUnavailable() {
    return this.state === G.unavailable;
  }
  get needsPlayParams() {
    return ["musicVideo", "song"].includes(this.type);
  }
  get normalizedType() {
    return normalizeContentType(this.type);
  }
  get offers() {
    return this.attributes.offers;
  }
  get offersHlsUrl() {
    const {offers: e} = this, n = null == e ? void 0 : e.find(e => {
      var n;
      return !!(null === (n = e.hlsUrl) || void 0 === n ? void 0 : n.length);
    });
    return null == n ? void 0 : n.hlsUrl;
  }
  get hasOffersHlsUrl() {
    return isStringNotEmpty(this.offersHlsUrl);
  }
  set playbackData (e) {
    if (void 0 === e) return;
    this.previewURL && (e.previewURL = this.previewURL);
    const n = transform$7(e);
    this.artwork && n.artwork && delete n.artwork, n.id !== this.id && delete n.id, this.playParams && n.attributes.playParams && (n.attributes.playParams = this.playParams), n.attributes = function (e) {
      for (var n = 1; n < arguments.length; n++) {
        var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
        "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
          return Object.getOwnPropertyDescriptor(d, e).enumerable;
        }))), h.forEach(function (n) {
          n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
        });
      }
      return e;
    }({}, this.attributes, n.attributes), Object.assign(this, n), U.debug("media-item: item merged with playbackData", this), this.state = G.ready;
  }
  get playbackDuration() {
    return this.attributes.durationInMillis || this.attributes.durationInMilliseconds;
  }
  get playEvent() {
    var e;
    return null === (e = this.defaultPlayable) || void 0 === e ? void 0 : e.playEvent;
  }
  get playlistArtworkURL() {
    var e, n, d;
    return this.hasPlaylistContainer && this.hasContainerArtwork ? null === (e = this.container) || void 0 === e || null === (n = e.attributes) || void 0 === n || null === (d = n.artwork) || void 0 === d ? void 0 : d.url : this.artworkURL;
  }
  get playlistName() {
    var e, n;
    return this.hasPlaylistContainer ? null === (e = this.container) || void 0 === e || null === (n = e.attributes) || void 0 === n ? void 0 : n.name : this.albumName;
  }
  get playParams() {
    return this.attributes.playParams;
  }
  get playRawAssetURL() {
    return this.offers ? this.offers.some(e => "STDQ" === e.type) : !(!this.isCloudUpload && !w[this.type]);
  }
  get previewURL() {
    var e, n, d, h, p, y, m, g, b, _, T, S, P, E, k;
    return (null === (e = this.attributes) || void 0 === e || null === (n = e.previews) || void 0 === n || null === (d = n[0]) || void 0 === d ? void 0 : d.url) || (null === (h = this.attributes) || void 0 === h || null === (p = h.previews) || void 0 === p || null === (y = "allow-forms") || void 0 === y ? void 0 : y.hlsUrl) || (null === (m = this.attributes) || void 0 === m || null === (g = m.trailers) || void 0 === g || null === (b = g[0]) || void 0 === b || null === (_ = b.assets) || void 0 === _ ? void 0 : _.hlsUrl) || (null === (T = this.attributes) || void 0 === T || null === (S = T.movieClips) || void 0 === S || null === (P = S[0]) || void 0 === P ? void 0 : P.hlsUrl) || (null === (E = this.attributes) || void 0 === E || null === (k = E.video) || void 0 === k ? void 0 : k.hlsUrl);
  }
  get rating() {
    return this.attributes.rating;
  }
  get releaseDate() {
    if (this._releaseDate) return this._releaseDate;
    if (this.attributes && (this.attributes.releaseDate || this.attributes.releaseDateTime)) {
      const e = this.attributes.releaseDate || this.attributes.releaseDateTime;
      return this._releaseDate = /^\d{4}-\d{1,2}-\d{1,2}/.test(e) ? new Date(e) : void 0, this._releaseDate;
    }
  }
  set releaseDate (e) {
    this._releaseDate = "string" == typeof e ? /^\d{4}-\d{1,2}-\d{1,2}/.test(e) ? new Date(e) : void 0 : "number" == typeof e ? new Date(e) : e;
  }
  get songId() {
    return this._songId && -1 !== this._songId ? this._songId : this.id;
  }
  get state() {
    return this._state.current;
  }
  set state (e) {
    const n = {oldState: this._state.current, state: e};
    this._stateWillChange && this._stateWillChange(this), this.dispatchEvent(Z, n), this._state.set(e), this._stateDidChange && this._stateDidChange(this), this.dispatchEvent(X, n);
  }
  get title() {
    return this.attributes.name || this.attributes.title;
  }
  get trackNumber() {
    return this.attributes.trackNumber;
  }
  beginMonitoringStateDidChange(e) {
    this._stateDidChange = e;
  }
  beginMonitoringStateWillChange(e) {
    this._stateWillChange = e;
  }
  endMonitoringStateDidChange() {
    this._stateDidChange = void 0;
  }
  endMonitoringStateWillChange() {
    this._stateWillChange = void 0;
  }
  isEqual(e) {
    return this.id === e.id && this.type === e.type && this.attributes === e.attributes;
  }
  resetState() {
    this.endMonitoringStateWillChange(), this.endMonitoringStateDidChange(), this.state = G.none;
  }
  restrict() {
    this.isExplicitItem && (this.state = G.restricted, this._removePlayableData());
  }
  notSupported() {
    this.state = G.unsupported, this._removePlayableData();
  }
  updateFromLoadError(e) {
    switch (e.errorCode) {
      case MKError.CONTENT_RESTRICTED:
        this.state = G.restricted;
        break;
      case MKError.CONTENT_UNAVAILABLE:
        this.state = G.unavailable;
        break;
      default:
        this.state = G.error;
    }
  }
  updateFromSongList(e) {
    "musicVideo" === this.type ? this.updateWithLoadedAssets(void 0, e["hls-playlist-url"]) : this.updateWithLoadedAssets(e.assets), this._songId = e.songId, this.updateWithLoadedKeys({"hls-key-cert-url": e["hls-key-cert-url"], "hls-key-server-url": e["hls-key-server-url"], "widevine-cert-url": e["widevine-cert-url"]});
  }
  updateWithLoadedKeys(e, n) {
    this.keyURLs = e, n && (this.keyServerQueryParameters = n);
  }
  updateWithLoadedAssets(e, n) {
    e && (this._assets = e), n && (this.assetURL = n);
  }
  _removePlayableData() {
    var e, n, d;
    null === (e = this.attributes) || void 0 === e || delete e.playParams, null === (n = this.attributes) || void 0 === n || delete n.previews, null === (d = this.attributes) || void 0 === d || delete d.trailers;
  }
  constructor(n = {}) {
    super([X, Z]), this.hlsMetadata = {}, this.attributes = {}, this.playbackType = e.PlaybackType.none, this._assets = [], this._state = createMediaItemStateGuard(), U.debug("media-item: creating Media Item with options:", n);
    n.id && n.attributes ? (Object.keys(n).forEach(e => {
      Object.prototype.hasOwnProperty.call(Object(ee), e) || (this[e] = n[e]);
    }), this.type = this.playParams && this.playParams.kind ? this.playParams.kind : this.type || "song") : (this.id = n.id || generateUUID(), this.type = n.type || "song", this.attributes = {playParams: {id: this.id, kind: this.type}}), this._context = n.context || {}, n.container ? this._container = n.container : n.containerId && n.containerType && (this._container = {id: n.containerId, type: n.containerType});
  }
}
