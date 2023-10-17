#include "mkdialog.h"

MKDialog::MKDialog()
{

}

void MKDialog::presentError(e) {
    const n = e.dialog;
    if (void 0 !== n) {
        MKDialog.serverDialog(n).present()
                else
                new MKDialog(e.message).present();
    }
}

static serverDialog(e) {
    const n = new this(e.message, e.explanation);
    return e.okButtonAction && e.okButtonAction.url && (n._okButtonActionURL = e.okButtonAction.url), e.okButtonString && (n._okButtonString = e.okButtonString), e.cancelButtonString && (n._cancelButtonString = e.cancelButtonString), n;
}
static clientDialog(e) {
    const n = new this(e.message, e.explanation);
    return e.okButtonAction && (n._okButtonAction = e.okButtonAction), e.cancelButtonAction && (n._cancelButtonAction = e.cancelButtonAction), e.okButtonString && (n._okButtonString = e.okButtonString), e.cancelButtonString && (n._cancelButtonString = e.cancelButtonString), n;
}
get actions() {
    return this.cancelButton ? `<div id="mk-dialog-actions">${this.cancelButton}${this.okButton}</div>` : `<div id="mk-dialog-actions">${this.okButton}</div>`;
}
get cancelButton() {
    if ("string" == typeof this._cancelButtonString) return `<button type="button">${this._cancelButtonString}</button>`;
}
set cancelButton (e) {
    this._cancelButtonString = e;
}
get explanation() {
    return `<p id="mk-dialog-explanation">${this._explanation}</p>`;
}
get hasOKButtonAction() {
    return !!this._okButtonActionURL || !!this._okButtonAction;
}
get message() {
    return `<h5 id="mk-dialog-title">${this._message}</h5>`;
}
get okButton() {
    return this.hasOKButtonAction && this._okButtonActionURL ? `<button type="button" data-ok-action-url='${this._okButtonActionURL}'>${this._okButtonString}</button>` : `<button type="button">${this._okButtonString}</button>`;
}
present() {
    const e = document.createDocumentFragment(), n = document.createElement("div");
    n.id = this.scrimId, e.appendChild(n);
    const d = document.createElement("div");
    d.id = this.id, d.classList.add("mk-dialog"), d.setAttribute("role", "alertDialog"), d.setAttribute("aria-modal", "true"), d.setAttribute("aria-labeledby", "mk-dialog-title"), d.setAttribute("aria-describedby", "mk-dialog-explanation");
    let h = `\n      <div id="mk-dialog-body">\n        ${this.message}\n        ${this.explanation}\n      </div>`;
    h = `\n      ${h}\n      ${this.actions}\n    `, d.innerHTML = h, e.appendChild(d), document.body.appendChild(e), document.querySelector(`#${d.id} #mk-dialog-actions *:first-child`).focus(), setTimeout(() => {
            document.querySelector(`#${d.id} #mk-dialog-actions *:first-child`).addEventListener("click", () => {
            this._cancelButtonAction && this._cancelButtonAction(), d.parentElement.removeChild(d), n.parentElement.removeChild(n);
}), this.hasOKButtonAction && (this._okButtonActionURL ? document.querySelector(`#${d.id} #mk-dialog-actions *:last-child`).addEventListener("click", e => {
            window.open(e.target.dataset.okActionUrl, "_blank"), d.parentElement.removeChild(d), n.parentElement.removeChild(n);
}) : this._okButtonAction && document.querySelector(`#${d.id} #mk-dialog-actions *:last-child`).addEventListener("click", e => {
            this._okButtonAction(), d.parentElement.removeChild(d), n.parentElement.removeChild(n);
}));
});
}
_appendStyle(e) {
    const n = document.createElement("style");
    n.id = this.styleId, n.styleSheet ? n.styleSheet.cssText = e : n.innerHTML = e, document.body.appendChild(n);
}
constructor(e, n = "") {
    this._message = e, this._explanation = n, this.id = "musickit-dialog", this.scrimId = this.id + "-scrim", this.styleId = this.id + "-style", this._okButtonString = "OK", [this.id, this.scrimId, this.styleId].forEach(e => {
            try {
            const n = document.getElementById(e);
            n.parentElement.removeChild(n);
} catch (Mr) {}
}), this._appendStyle("\n#musickit-dialog {\n  --mk-dialog-background: rgba(255, 255, 255, 1);\n  --mk-dialog-text: rgba(0, 0, 0, 0.95);\n  --mk-dialog-border: rgba(0, 0, 0, 0.07);\n  --mk-dialog-scrim: rgba(255, 255, 255, 0.8);\n  --mk-dialog-primary: rgba(0, 122, 255, 1);\n}\n\n@media (prefers-color-scheme: dark) {\n  #musickit-dialog {\n      --mk-dialog-background: rgba(30, 30, 30, 1);\n      --mk-dialog-text: rgba(255, 255, 255, 0.85);\n      --mk-dialog-border: rgba(255, 255, 255, 0.1);\n      --mk-dialog-scrim: rgba(38, 38, 38, 0.8);\n      --mk-dialog-primary: rgba(8, 132, 255, 1);\n  }\n}\n\n#musickit-dialog-scrim {\n  position: fixed;\n  top: 0;\n  left: 0;\n  right: 0;\n  bottom: 0;\n  width: 100%;\n  height: 100%;\n  background: rgba(0, 0, 0, 0.35);\n}\n\n#musickit-dialog * {\n  -webkit-tap-highlight-color: transparent;\n  -webkit-touch-callout: none;\n  -ms-touch-action: none;\n  -webkit-user-select: none;\n  -moz-user-select: none;\n  -ms-user-select: none;\n  user-select: none;\n  font-family: -apple-system, SF UI Text, Helvetica Neue, Helvetica, sans-serif;\n  font-size: 15px;\n  line-height: 20px;\n}\n\n#musickit-dialog *:focus { outline: 0; }\n\n#musickit-dialog {\n  display: -webkit-box;\n  display: -moz-box;\n  display: -ms-flexbox;\n  display: -webkit-flex;\n  display: flex;\n  -webkit-flex-direction: column;\n  -moz-flex-direction: column;\n  flex-direction: column;\n  -webkit-justify-content: space-between;\n  -moz-justify-content: space-between;\n  justify-content: space-between;\n  min-width: 277px;\n  max-width: 290px;\n  min-height: 109px;\n  background: var(--mk-dialog-background);\n  box-shadow: 0px 0px 9px rgba(0, 0, 0, 0.18);\n  border-radius: 10px;\n  color: var(--mk-dialog-text);\n  position: fixed;\n  top: 50%;\n  left: 50%;\n  margin-left: -142px;\n  margin-top: -67px;\n  z-index: 9999999999999999999999999;\n}\n\n#musickit-dialog #mk-dialog-body {\n  display: -webkit-box;\n  display: -moz-box;\n  display: -ms-flexbox;\n  display: -webkit-flex;\n  display: flex;\n  -webkit-flex-direction: column;\n  -moz-flex-direction: column;\n  flex-direction: column;\n  flex-grow: 1;\n  -webkit-justify-content: space-evenly;\n  -moz-justify-content: space-evenly;\n  justify-content: space-evenly;\n  -webkit-align-items: stretch;\n  align-items: stretch;\n  padding: 10px 20px;\n  min-height: 74px;\n  text-align: center;\n}\n\n#musickit-dialog .mk-dialog h5 {\n  font-weight: 500;\n  line-height: 20px;\n  margin: 7px 0 0 0;\n  padding: 0;\n}\n\n#musickit-dialog .mk-dialog p {\n  margin: 0 0 7px 0;\n  padding: 0;\n  paddin-top: 3px;\n  line-height: 18px;\n  font-size: 13px;\n  font-weight: 300;\n}\n\n#musickit-dialog #mk-dialog-actions {\n  border-top: 1px solid var(--mk-dialog-border);\n  display: -webkit-box;\n  display: -moz-box;\n  display: -ms-flexbox;\n  display: -webkit-flex;\n  display: flex;\n  -webkit-flex-direction: row;\n  -moz-flex-direction: colrowumn;\n  flex-direction: row;\n  max-height: 41px;\n  min-height: 34px;\n  -webkit-justify-self: flex-end;\n  -moz-justify-self: flex-end;\n  justify-self: flex-end;\n}\n\n#musickit-dialog #mk-dialog-actions button {\n  flex-grow: 1;\n  border: 0;\n  background: none;\n  color: var(--mk-dialog-primary);\n  padding: 0;\n  margin: 0;\n  min-height: 34px;\n  height: 41px;\n  text-align: center;\n}\n\n#musickit-dialog #mk-dialog-actions *:nth-child(2) {\n  border-left: 1px solid var(--mk-dialog-border);\n  font-weight: 500;\n}\n");
}
}
