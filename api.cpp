#include "api.h"

API::API(e, n)
{
    if (this.prefix = "ï£¿", this.method = "GET", this.url = e, (n = n || {}).storage && n.underlyingStorage) throw new Error("only pass storage OR underlyingStorage in sessionOptions to URLSession");
        const d = n.underlyingStorage || {};
        if (this.storage = n.storage || new GenericStorage(d), this.networkCache = new NetworkCache({storage: this.storage, prefix: this.prefix, cacheKeyFunction: this._key.bind(this)}), this.ttl = n.ttl || 3e5, this._fetchOptions = _objectSpread$D({}, n.fetchOptions), "function" != typeof n.fetch && "function" != typeof fetch) throw new Error("window.fetch is not defined");
        var h;
        this._fetchFunction = null !== (h = n.fetch) && void 0 !== h ? h : fetch.bind(window), this.headers = this._fetchOptions.headers || new Headers, delete this._fetchOptions.headers;
    }
}

API::API(e, n, d) {
        super(e, d), this._developerToken = new DeveloperToken(n), this.headers.set("Authorization", "Bearer " + this.developerToken), d = d || {}, this.userToken = d.userToken, this.userToken && this.headers.set("Media-User-Token", this.userToken);
    }
}

API::API(e, n, d, h, p, y, m = {}, g) {
            super(e, n, _objectSpreadProps$2(function (e) {
                                                 for (var n = 1; n < arguments.length; n++) {
                                                     var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
                                                     "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
                                                         return Object.getOwnPropertyDescriptor(d, e).enumerable;
                                                     }))), h.forEach(function (n) {
                                                         n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
                                                     });
                                                 }
                                                 return e;
                                             }({}, g), {userToken: h, storage: y})), this.storefrontId = Me.ID, this.resourceRelatives = {artists: {albums: {include: "tracks"}, playlists: {include: "tracks"}, songs: null}}, this.defaultIncludePaginationMetadata = m.features && Object.prototype.hasOwnProperty.call(Object(m.features), "api-pagination-metadata"), this._store = new LocalDataStore(m), d && (this.storefrontId = d.toLowerCase()), h && p && (this.userStorefrontId = p.toLowerCase()), this.v3 = new MediaAPIV3({developerToken: n, mediaUserToken: h, storefrontId: d, realmConfig: {music: {url: e.replace(/\/v[0-9]+(\/)?$/, "")}}});
        }
}

void API::clearCacheForRequest(e, n) {
    "object" == typeof e && (n = e, e = void 0);
    const d = this.constructURL(e, n);
    this.networkCache.removeItemsMatching(d);
}

auto API::request(e, n, d) {
    var h, p = this;
    return (h = function* () {
            d || "object" != typeof e || (d = n || {}, n = e, e = void 0);
            let h = {};
            "object" == typeof (d = _objectSpread$D({method: p.method, headers: p.headers, reload: false}, p._fetchOptions, d)).queryParameters ? (h = d.queryParameters, delete d.queryParameters) : "GET" !== d.method && "DELETE" !== d.method || (h = n);
            const y = p.constructURL(e, h), {method: m, reload: g = false, useRawResponse: b} = d;
            if (d.headers = p.buildHeaders(d), delete d.reload, delete d.useRawResponse, "GET" === m && !g) {
            const e = p.getCacheItem(y);
            if (e) return Promise.resolve(e);
}
            n && Object.keys(n).length && ("POST" === m || "PUT" === m) && (d.body = d.body || n, d.contentType === jr.FORM ? (d.body = urlEncodeParameters(d.body), d.headers.set("Content-Type", jr.FORM)) : (d.body = JSON.stringify(d.body), d.headers.set("Content-Type", jr.JSON)));
            const _ = yield p._fetchFunction(y, d);
            if (!_.ok) return Promise.reject(_);
            let T;
            try {
            T = yield _.json();
} catch (Mr) {
            T = {};
}
            if (T.errors) return Promise.reject(T.errors);
            const S = b ? T : T.results || T.data || T;
            if ("GET" === m) {
            var P;
            const e = null !== (P = getMaxAgeFromHeaders(_.headers)) && void 0 !== P ? P : p.ttl;
            p.setCacheItem(y, S, e);
}
            return S;
}, function () {
                var e = this, n = arguments;
                return new Promise(function (d, p) {
                    var y = h.apply(e, n);
                    function _next(e) {
                        asyncGeneratorStep$$(y, d, p, _next, _throw, "next", e);
                    }
                    function _throw(e) {
                        asyncGeneratorStep$$(y, d, p, _next, _throw, "throw", e);
                    }
                    _next(void 0);
                });
            })();
}

auto API::buildHeaders({headers: e, reload: n = false} = {}) {
    void 0 === e && (e = this.headers);
    const d = (e => new e.constructor(e))(e);
    return n && d.set("Cache-Control", "no-cache"), d;
}
QUrl API::constructURL(e, n) {
    return d = this.url, h = n, addQueryParamsToURL(addPathToURL(d, e), h);
    var d, h;
}
auto API::getCacheItem(e) {
    const n = this.networkCache.storage, d = `${this.prefix}${this.prefix}cache-mut`, h = n.getItem(d) || null, p = this.headers.get("Music-User-Token") || this.headers.get("Media-User-Token") || null;
    return p !== h && (this.networkCache.clear(), null === p ? n.removeItem(d) : n.setItem(d, p)), this.networkCache.getItem(e);
}
void API::setCacheItem(e, n, d = this.ttl) {
    this.networkCache.setItem(e, n, d);
}
void API::clearNetworkCache() {
    this.networkCache.clear();
}
_key(e, n) {
    const d = function (e) {
            try {
            const [n, d] = e.split("?", 2);
            if (void 0 === d) return n;
            const h = d.split("&").map(e => e.split("=", 2)), p = [...Array(h.length).keys()];
            p.sort((e, n) => {
        const d = h[e], p = h[n];
        return d < p ? -1 : d > p ? 1 : e - n;
    });
    const y = p.map(e => h[e]);
    return `${n}?${y.map(([e, n]) => void 0 !== n ? `${e}=${n}` : e).join("&")}`;
} catch (Mr) {
    return e;
}
}(e).toLowerCase().replace(this.url, "");
return `${this.prefix}${d.replace(/[^-_0-9a-z]{1,}/g, ".")}`;
}

} {
get developerToken() {
    return this._developerToken.token;
}

} {
get needsEquivalents() {
    const {userStorefrontId: e} = this;
           return void 0 !== e && "" !== e && e !== this.storefrontId;
          }

}
