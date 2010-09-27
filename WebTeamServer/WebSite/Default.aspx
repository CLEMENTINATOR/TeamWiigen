<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebSite.Default" %>

<%@ MasterType VirtualPath="~/MasterPage.Master" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <p>Welcome on the official TeamWiigen web site.<br />
    THIS SITE IS STILL UNDER CONSTRUCTION.</p>
    <br />
    <br />
    <p>Our first release: <asp:HyperLink runat="server" NavigateUrl="~/downloads/libs/libwiisys.zip">Libwiisys</asp:HyperLink><br />
    <asp:HyperLink runat="server" NavigateUrl="~/doc/html/Index.html" Target="_blank">Doc</asp:HyperLink>, 
    <asp:HyperLink runat="server" NavigateUrl="~/downloads/portlibs/plibs_libwiisys.zip">portlibs</asp:HyperLink>, 
    <asp:HyperLink runat="server" NavigateUrl="htpp://svn2.xp-dev.com/svn/Libwiisys/" Target="_blank">SVN</asp:HyperLink></p>
</asp:Content>
