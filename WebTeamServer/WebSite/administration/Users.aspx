<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true"
    CodeBehind="Users.aspx.cs" Inherits="WebSite.administration.Users" %>

<%@ MasterType VirtualPath="~/MasterPage.Master" %>
<%@ Import Namespace="System.Linq" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div>
        <asp:Label runat="server" Text="Login" />
        <asp:TextBox ID="tbxLogin" runat="server" />
        <asp:Label runat="server" Text="Mail" />
        <asp:TextBox ID="tbxMail" runat="server" />
    </div>
    <br />
    <asp:Button ID="btnRecherche" runat="server" Text="Search" 
        onclick="btnRecherche_Click" />
    <br />
    <br />
    <asp:GridView ID="grvUsers" runat="server" oninit="grvUsers_Init" 
        onrowcommand="grvUsers_RowCommand">
        <Columns>
            <asp:TemplateField HeaderText="Login">
                <ItemTemplate>
                    <asp:Label runat="server" Text='<%# Eval("Login") %>' />
                </ItemTemplate>
            </asp:TemplateField>
            <asp:TemplateField HeaderText="Mail">
                <ItemTemplate>
                    <asp:Label runat="server" Text='<%# Eval("Mail") %>' />
                </ItemTemplate>
            </asp:TemplateField>
            <asp:TemplateField>
                <ItemTemplate>
                    <asp:HyperLink runat="server" NavigateUrl='<%# "~/administration/UserRights.aspx?user=" + Eval("Id") %>' ImageUrl="~/img/AddUserRight.png" ToolTip="Associate right" />
                </ItemTemplate>
            </asp:TemplateField>
            <asp:TemplateField>
                <ItemTemplate>
                    <asp:HyperLink runat="server" NavigateUrl='<%# "~/administration/UserRoles.aspx?user=" + Eval("Id") %>' ImageUrl="~/img/AddUserRole.png" ToolTip="Associate role" />
                </ItemTemplate>
            </asp:TemplateField>
            <asp:TemplateField>
                <ItemTemplate>
                    <asp:ImageButton runat="server" CommandName="sup" CommandArgument='<%# Eval("Id") %>' ImageUrl="~/img/delete.png" ToolTip="Delete user" AlternateText="Delete" />
                </ItemTemplate>
            </asp:TemplateField>
        </Columns>
    </asp:GridView>
    <br />
    <asp:HyperLink ID="lnkNewUser" runat="server" Text="New User" OnInit="lnkNewUser_Init" NavigateUrl="~/administration/NewUser.aspx" />
</asp:Content>
