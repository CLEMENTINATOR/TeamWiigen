function postBackByObject(mEvent) {
    var o;
    // Internet Explorer    
    if (mEvent.srcElement) {
        o = mEvent.srcElement;
    }
    // Netscape and Firefox
    else if (mEvent.target) {
        o = mEvent.target;
    }
    if (o.tagName == "INPUT" && o.type == "checkbox") {
        __doPostBack("", "");
    }
}