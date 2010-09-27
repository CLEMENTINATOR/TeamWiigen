using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.UI;
using System.Web;
using System.Net;
using WebSiteModel;

namespace WebFramework
{
    public class PageBase : Page
    {
        public List<int> RequiredRights;
        protected bool UserAttached { get; set; }

        protected tw_web DbInstance
        {
            get;
            private set;
        }

        public PageBase()
        {
            RequiredRights = new List<int>();
            DbInstance = new tw_web();
            UserAttached = false;
            WebSession.UserCalled += new Action<User>(WebSession_UserCalled);
        }

        public override void Dispose()
        {
            WebSession.UserCalled -= new Action<User>(WebSession_UserCalled);
            base.Dispose();
        }

        void WebSession_UserCalled(User u)
        {
            if (!UserAttached && u != null)
            {
                DbInstance.AttachTo("Users", u);
                UserAttached = true;
            }
        }

        private string LoginUrl
        {
            get
            {
                return "~/Authentication.aspx?redirectUrl=" + Server.UrlEncode(Request.RawUrl);
            }
        }

        protected override void OnPreInit(EventArgs e)
        {
            bool allowAccess = RequiredRights.Count == 0;

            if (!allowAccess && WebSession.User == null)
                Response.Redirect(LoginUrl, true);

            if (!allowAccess && WebSession.User != null)
            {
                foreach (int right in WebSession.User.AllUserRights)
                    if (RequiredRights.Contains(right))
                    {
                        allowAccess = true;
                        break;
                    }
            }

            if (!allowAccess)
            {
                Response.StatusCode = (int)HttpStatusCode.Forbidden;
                Response.End();
            }

            base.OnPreInit(e);
        }

        protected override void OnUnload(EventArgs e)
        {
            if (UserAttached)
            {
                DbInstance.Detach(WebSession.User);
                UserAttached = false;
            }
            base.OnUnload(e);
        }
    }
}
