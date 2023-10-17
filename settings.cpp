#include "settings.h"

Settings::Settings()
{

}
class Settings {
  set(e, n) {
    this.get(e) || "" === n || (this.values[e] = n);
  }
  get(e, n, d) {
    return "object" == typeof n && "string" == typeof d ? this.has(e) ? this.values[e] : n[d] : this.has(e) ? this.values[e] : n;
  }
  has(e) {
    return e in this.values;
  }
  alt(e, n, d) {
    for (let h = 0; h < d.length; ++h) if (n === d[h]) {
      this.set(e, n);
      break;
    }
  }
  integer(e, n) {
    /^-?\d+$/.test(n) && this.set(e, parseInt(n, 10));
  }
  percent(e, n) {
    if (n.match(/^([\d]{1,3})(\.[\d]*)?%$/)) try {
      const d = parseFloat(n);
      if (d >= 0 && d <= 100) return this.set(e, d), true;
    } catch (Mc) {
      return false;
    }
    return false;
  }
  constructor() {
    this.values = {};
  }
}
