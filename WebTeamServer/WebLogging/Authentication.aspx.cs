using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Security;

namespace WebLogging
{
    public partial class Authentication : System.Web.UI.Page
    {
        protected void Login1_Authenticate(object sender, AuthenticateEventArgs e)
        {
            if (FormsAuthentication.Authenticate(Login1.UserName, Login1.Password))
                FormsAuthentication.RedirectFromLoginPage(Login1.UserName, false);
        }
    }
}