using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WebSiteModel;

namespace WebFramework
{
    public class MenuItem
    {
        public string Url
        {
            internal set;
            get;
        }

        public string Text
        {
            internal set;
            get;
        }

        internal List<int> AssociatedRights
        {
            get;
            private set;
        }

        internal MenuItem()
        {
            AssociatedRights = new List<int>();
        }

        public bool AsAccess(User user)
        {
            if (AssociatedRights.Count == 0)
                return true;
            else if(user != null)
                foreach (int id in user.AllUserRights)
                    if (AssociatedRights.Contains(id))
                        return true;

            return false;
        }
    }
}
