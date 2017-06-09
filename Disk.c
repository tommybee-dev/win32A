#include "Common.h"


TCHAR g_szText[ ]  = _T("Drive Total_clus Available_clus Sec/Cluster Bytes/Sec\n");
TCHAR g_szText1[ ] = _T("----- ---------- -------------- ----------- ---------\n");
TCHAR g_szInfo[ ]  = _T("->                                                   \n");

// ...for data display format...
// right justified, thousand comma separated and other format for displayed data
void utoiRightJustified(TCHAR* szLeft, TCHAR* szRight, unsigned uValue)
{
   TCHAR* szCur = szRight;
   int nComma = 0;
   if(uValue)
   {
      while(uValue && (szCur >= szLeft))
         {
         if(nComma == 3)
               {
            *szCur = ',';
            nComma = 0;
         }
         else
               {
            *szCur = (uValue % 10) | 0x30;
            uValue /= 10;
            ++nComma;
         }
         --szCur;
      }
   }
   else
   {
      *szCur = '0';
      --szCur;
   }
 if(uValue)
   {
      szCur = szLeft;
      while(szCur <= szRight)
         { // if not enough field to display the data...
         *szCur = '*';
         ++szCur;
      }
   }
}

int printLocalSpaces()
{
   TCHAR szMsg[4200];
   struct _diskfree_t df = {0};
   // search drives and assigns the bit masks to uDriveMask variable...
   ULONG uDriveMask = _getdrives();
   unsigned uErr, uLen, uDrive;
   printf("clus - cluster, sec - sector\n");
   // may need a casting from TCHAR to char * here
   // printf((char *)g_szText);
   printf(g_szText);
   printf(g_szText1);
   for(uDrive = 1; uDrive <= 26; ++uDrive)
   {
      // if the drive is available...
      if(uDriveMask & 1)
         { // call _getdiskfree()...
         uErr = _getdiskfree(uDrive, &df);
         // provide some storage
         memcpy(szMsg, g_szInfo, sizeof(g_szInfo));
         szMsg[3] = uDrive + 'A' - 1;

         // if _getdiskfree() is no error, display the data
         if(uErr == 0)
               {
            utoiRightJustified(szMsg+4, szMsg+15, df.total_clusters);
            utoiRightJustified(szMsg+18, szMsg+29, df.avail_clusters);
            utoiRightJustified(szMsg+27, szMsg+37, df.sectors_per_cluster);
            utoiRightJustified(szMsg+40, szMsg+50, df.bytes_per_sector);
         }
         else
           {// print system message and left other fields empty
            uLen = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, uErr, 0, szMsg+8, 4100, NULL);
            szMsg[uLen+6] = ' ';
            szMsg[uLen+7] = ' ';
            szMsg[uLen+8] = ' ';
         }
         printf(szMsg);
      }
      // shift right the found drive bit masks and repeat the process
      uDriveMask >>= 1;
   }
   return 0;
}
