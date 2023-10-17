#include "notifications.h"

Notifications::Notifications()
{
    /*  constructor(e = [], n) {
    this._eventRegistry = {}, e.forEach(e => {
      this._eventRegistry[e] = [];
    }), n && n.namespace && (this.dispatchNamespace = "com.apple." + n.namespace), this.shouldStorageDispatch && (this._handleGlobalStorageEvent = this._handleGlobalStorageEvent.bind(this), window.addEventListener("storage", this._handleGlobalStorageEvent));
  }*/
}

bool Notifications::shouldStorageDispatch() {
    return "undefined" != typeof window && hasSessionStorage() && this.dispatchNamespace;
}

void Notifications::addEventListener(e, n) {
    Array.isArray(this._eventRegistry[e]) && this._eventRegistry[e].push(n);
}

void Notifications::dispatchEvent(e, n) {
    Array.isArray(this._eventRegistry[e]) && this._eventRegistry[e].forEach(e => e(n));
}

void Notifications::dispatchDistributedEvent(e, n) {
    if (this.dispatchEvent(e, n), this.shouldStorageDispatch) {
        var d;
        const h = `${this.dispatchNamespace}:${e}`;
        null === (d = getSessionStorage()) || void 0 === d || d.setItem(h, JSON.stringify(n));
    }
}

void Notifications::removeEventListener(e, n) {
    if (Array.isArray(this._eventRegistry[e])) {
        const d = this._eventRegistry[e].indexOf(n);
        this._eventRegistry[e].splice(d, 1);
    }
}
void Notifications::_handleGlobalStorageEvent(e) {
    var n;
    if (this.dispatchNamespace && (null === (n = e.key) || void 0 === n ? void 0 : n.startsWith(this.dispatchNamespace + ":"))) {
        const n = e.key.substring(this.dispatchNamespace.length + 1);
        this.dispatchEvent(n, JSON.parse(e.newValue));
    }
}

}
