CREATE TABLE [dbo].[LOG] (
    [LOG_ID]            INT            IDENTITY (1, 1) NOT NULL,
    [LOG_APV_ID]        INT            NOT NULL,
    [LOG_LTY_ID]        INT            NOT NULL,
    [LOG_MESSAGE]       NVARCHAR (255) NOT NULL,
    [LOG_SOURCE]        NVARCHAR (255) NOT NULL,
    [LOG_LINE]          INT            NOT NULL,
    [LOG_CREATION_DATE] DATETIME       NOT NULL,
    [LOG_USER_IP]       VARCHAR (15)   NOT NULL
);

