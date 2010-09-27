using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebFramework;

namespace WebSite
{
    public partial class Login : System.Web.UI.UserControl
    {
        protected string LoginUrl
        {
            get
            {
                return "~/Authentication.aspx?redirectUrl=" + Server.UrlEncode(Request.RawUrl);
            }
        }

        protected override void OnInit(EventArgs e)
        {
            hypLogin.NavigateUrl = LoginUrl;
            if (WebSession.User != null)
                litVisitor.Text = "Welcome <b>" + WebSession.User.Login + "</b>";
            hypLogin.Visible = (WebSession.User == null);
            litVisitor.Visible = !hypLogin.Visible;
            base.OnInit(e);
        }
    }
}