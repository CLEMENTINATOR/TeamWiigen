using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Security;
using WebSiteModel;
using WebFramework;

namespace WebLogging
{
    public partial class Authentication : PageBase
    {
        protected override void OnPreInit(EventArgs e)
        {
            Master.Title = "Login";
            base.OnPreInit(e);
        }

        protected override void OnInit(EventArgs e)
        {
            tbxLogin.Focus();
            base.OnInit(e);
        }

        private string RedirectPage
        {
            get
            {
                string param = Request.Params["redirectUrl"];
                if (param == null)
                    return "~/Default.aspx";
                else
                    return "~" + param;
            }
        }

        protected void btnLogin_onClick(object sender, EventArgs args)
        {
            var users = from u in DbInstance.Users
                         where u.Login == tbxLogin.Text && u.Password == tbxPassword.Text
                         select u;

            lblBadLogin.Visible = (users.Count() == 0);

            if (users.Count() == 1)
            {
                lblBadLogin.Visible = false;
                UserAttached = true;
                WebSession.User = users.First();                
                Response.Redirect(RedirectPage, true);
            }
            else
                lblBadLogin.Visible = true;
        }

        
    }
}