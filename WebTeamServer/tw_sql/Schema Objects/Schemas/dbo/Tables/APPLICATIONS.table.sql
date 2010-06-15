CREATE TABLE [dbo].[APPLICATIONS] (
    [APP_ID]            INT           IDENTITY (1, 1) NOT NULL,
    [APP_NAME]          NVARCHAR (50) NOT NULL,
    [APP_CREATION_DATE] DATE          NOT NULL
);

