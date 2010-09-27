using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WebSiteModel;

namespace WebFramework
{
    public class MenuManager
    {
        Dictionary<MenuItem, List<MenuItem>> menuList;

        private static MenuManager _current;
        public static MenuManager Instance
        {
            get
            {
                if (_current == null)
                    _current = new MenuManager();
                return _current;
            }
        }

        public IEnumerable<MenuItem> GetFrontMenuList(User user)
        {
            foreach (MenuItem menu in menuList.Keys)
                if (menu.AsAccess(user))
                {
                    if (String.IsNullOrEmpty(menu.Url))
                    {
                        IEnumerable<MenuItem> subItems = GetSideMenuList(user, menu.Text);
                        if (subItems.Count() > 0)
                            yield return new MenuItem { Text = menu.Text, Url = subItems.First().Url };
                    }
                    else
                        yield return menu;
                }
        }

        public IEnumerable<MenuItem> GetSideMenuList(User user, string section)
        {
            foreach (MenuItem front in menuList.Keys)
                if (front.AsAccess(user) && front.Text == section)
                {
                    foreach (MenuItem menu in menuList[front])
                        if (menu.AsAccess(user))
                            yield return menu;
                }
        }

        private MenuManager()
        {
            menuList = new Dictionary<MenuItem, List<MenuItem>>();
            MenuItem mainItem = null;
            MenuItem childItem = null;
            List<MenuItem> subItems = null;

            //Main Page
            mainItem = new MenuItem { Url = "~/", Text = "Main Page" };
            menuList.Add(mainItem, new List<MenuItem>());

            //Report page
            mainItem = new MenuItem { Text = "Reporting" };
            mainItem.AssociatedRights.Add(RightList.Reporting);
            subItems = new List<MenuItem>();
            subItems.Add(new MenuItem { Text = "Web Logger", Url = "~/WebLogging/Viewer.aspx" });
            menuList.Add(mainItem, subItems);

            //Administration
            mainItem = new MenuItem { Text = "Administration" };
            mainItem.AssociatedRights.Add(RightList.Administration);
            subItems = new List<MenuItem>();
            childItem = new MenuItem { Text = "Users", Url = "~/administration/Users.aspx" };
            childItem.AssociatedRights.Add(RightList.Users);
            subItems.Add(childItem);
            menuList.Add(mainItem, subItems);
        }
    }
}
