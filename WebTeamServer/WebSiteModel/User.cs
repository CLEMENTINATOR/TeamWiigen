using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Objects.DataClasses;

namespace WebSiteModel
{
    public partial class User
    {
        public IQueryable<int> AllUserRights
        {
            get
            {
                Rights.Load();
                Roles.Load();
                IEnumerable<int> rights = from r in Rights select r.Id;
                foreach (Role r in Roles)
                {
                    r.Rights.Load();
                    rights = rights.Union(from rght in r.Rights select r.Id);
                }
                return rights.AsQueryable();
            }
        }
    }
}
