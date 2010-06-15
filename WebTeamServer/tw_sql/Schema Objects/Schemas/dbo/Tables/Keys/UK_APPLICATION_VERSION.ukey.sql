﻿ALTER TABLE [dbo].[APPLICATION_VERSION]
    ADD CONSTRAINT [UK_APPLICATION_VERSION] UNIQUE NONCLUSTERED ([APV_APP_ID] ASC, [APV_VALUE] ASC) WITH (ALLOW_PAGE_LOCKS = ON, ALLOW_ROW_LOCKS = ON, PAD_INDEX = OFF, IGNORE_DUP_KEY = OFF, STATISTICS_NORECOMPUTE = OFF) ON [PRIMARY];

