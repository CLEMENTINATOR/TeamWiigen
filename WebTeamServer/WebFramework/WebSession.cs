using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WebSiteModel;
using System.Web;

namespace WebFramework
{
    public class WebSession
    {
        public static User User
        {
            get
            {
                User u = HttpContext.Current.Session["User"] as User;
                UserCalled(u);
                return u;
            }

            set
            {
                HttpContext.Current.Session["User"] = value;
            }
        }

        public static event Action<User> UserCalled;
    }
}
