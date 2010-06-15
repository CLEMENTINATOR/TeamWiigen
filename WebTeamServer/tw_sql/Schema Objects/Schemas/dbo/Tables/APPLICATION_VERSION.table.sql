CREATE TABLE [dbo].[APPLICATION_VERSION] (
    [APV_ID]            INT           IDENTITY (1, 1) NOT NULL,
    [APV_APP_ID]        INT           NOT NULL,
    [APV_VALUE]         NVARCHAR (10) NOT NULL,
    [APV_CREATION_DATE] DATE          NOT NULL
);

