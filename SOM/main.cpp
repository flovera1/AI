//------------------------------------------------------------------------
//
//  Name:  SOMDemo (part one)
//
//  Desc:  Code to accompany part one of the SOM tutorial found at  
//         www.ai-junkie.com.
//         This demo creates a Kohonen Self Organizing Feature Map and 
//         uses it to classify a varying amount of colors. 
//         
//  Author:Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <windows.h>
#include <time.h>

#include "constants.h"
#include "utils.h"
#include "CController.h"
#include "resource.h"


//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "Kohonen Self Organizing Map Demo";
char* g_szWindowClassName = "MyWindowClass";

CController* g_Controller;



//---------------------------- WindowProc ---------------------------------
//  
//  This is the callback function which handles all the windows messages
//-------------------------------------------------------------------------

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{
 
   //these hold the dimensions of the client window area
   static int cxClient, cyClient; 

   //used to create the back buffer
   static HDC   hdcBackBuffer;
   static HBITMAP hBitmap;
   static HBITMAP hOldBitmap;


    switch (msg)
    {
  
    case WM_CREATE:
      {
         //to get get the size of the client window first we need  to create
         //a RECT and then ask Windows to fill in our RECT structure with
         //the client window size. Then we assign to cxClient and cyClient 
         //accordingly
         RECT rect;

         GetClientRect(hwnd, &rect);

         cxClient = rect.right;
         cyClient = rect.bottom;

         //seed random number generator
         srand((unsigned) time(NULL));

         
         //---------------create a surface to render to(backbuffer)

         //create a memory device context
         hdcBackBuffer = CreateCompatibleDC(NULL);

         //get the DC for the front buffer
         HDC hdc = GetDC(hwnd);

         hBitmap = CreateCompatibleBitmap(hdc,
                                          cxClient,
                                          cyClient);

        
         //select the bitmap into the memory device context
         hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

         //don't forget to release the DC
         ReleaseDC(hwnd, hdc);   
         
         //create the controller
         g_Controller = new CController(cxClient,
                                        cyClient,
                                        constNumCellsAcross,
                                        constNumCellsDown,
                                        constNumIterations);
      }

      break;

    case WM_KEYUP:
      {
        switch(wParam)
        {
         case VK_ESCAPE:
          {
            SendMessage(hwnd, WM_DESTROY, NULL, NULL);
            
            PostQuitMessage(0);
          }
          
          break;

          case 'R':
          {
           delete g_Controller;

           g_Controller = new CController(cxClient,
                                        cyClient,
                                        constNumCellsAcross,
                                        constNumCellsDown,
                                        constNumIterations);
          }
          
          break;
        }
      }

    
    case WM_PAINT:
      {
           
         PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);

        //fill the backbuffer with white
         BitBlt(hdcBackBuffer,
                0,
                0,
                cxClient,
                cyClient,
                NULL,
                NULL,
                NULL,
                WHITENESS);
          
         

        g_Controller->Render(hdcBackBuffer);


         //now blit the backbuffer to the front
         BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 
          
         EndPaint (hwnd, &ps);

      }

      break;

    //has the user resized the client area?
    case WM_SIZE:
      {
        //if so we need to update our variables so that any drawing
        //we do using cxClient and cyClient is scaled accordingly
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

      //now to resize the backbuffer accordingly. First select
      //the old bitmap back into the DC
      SelectObject(hdcBackBuffer, hOldBitmap);

      //don't forget to do this or you will get resource leaks
      DeleteObject(hBitmap); 

      //get the DC for the application
      HDC hdc = GetDC(hwnd);

      //create another bitmap of the same size and mode
      //as the application
      hBitmap = CreateCompatibleBitmap(hdc,
                      cxClient,
                      cyClient);

      ReleaseDC(hwnd, hdc);
      
      //select the new bitmap into the DC
      SelectObject(hdcBackBuffer, hBitmap);

      }

      break;
          
     case WM_DESTROY:
       {

         //clean up our backbuffer objects
         SelectObject(hdcBackBuffer, hOldBitmap);

         DeleteDC(hdcBackBuffer);
         DeleteObject(hBitmap); 
         
         // kill the application, this sends a WM_QUIT message  
         PostQuitMessage (0);
       }

       break;

     }//end switch

     //this is where all the messages not specifically handled by our 
     //winproc are sent to be processed
     return DefWindowProc (hwnd, msg, wParam, lParam);
}

//-------------------------------- WinMain -------------------------------
//
//  The entry point of the windows program
//------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine, 
                    int       iCmdShow)
{
   //handle to our window
   HWND           hWnd;
    
   //our window class structure
   WNDCLASSEX     winclass;
     
   // first fill in the window class stucture
   winclass.cbSize        = sizeof(WNDCLASSEX);
   winclass.style         = CS_HREDRAW | CS_VREDRAW;
   winclass.lpfnWndProc   = WindowProc;
   winclass.cbClsExtra    = 0;
   winclass.cbWndExtra    = 0;
   winclass.hInstance     = hInstance;
   winclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
   winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
   winclass.hbrBackground = NULL;
   winclass.lpszMenuName  = NULL;
   winclass.lpszClassName = g_szWindowClassName;
   winclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

   //register the window class
   if (!RegisterClassEx(&winclass))
   {
     MessageBox(NULL, "Registration Failed!", "Error", 0);

     //exit the application
     return 0;
   }

   //create a window with the *client* area specified.
   RECT rect;
   rect.left   =0;
   rect.top    = 0;
   rect.bottom = constWindowHeight;
   rect.right  = constWindowWidth;

   if (!AdjustWindowRectEx(&rect, CS_HREDRAW | CS_VREDRAW, true, NULL))
   {
     MessageBox(NULL, "Problem creating window", "error!", MB_OK);
     return 0;
   }

   //create the window and assign its ID to hwnd    
   hWnd = CreateWindowEx (NULL,                 // extended style
                          g_szWindowClassName,  // window class name
                          g_szApplicationName,  // window caption
                          WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
                          GetSystemMetrics(SM_CXSCREEN)/2 - constWindowWidth/2,
                          GetSystemMetrics(SM_CYSCREEN)/2 - constWindowHeight/2,                    
                          rect.right,           // initial x size
                          rect.bottom,          // initial y size
                          NULL,                 // parent window handle
                          NULL,                 // window menu handle
                          hInstance,            // program instance handle
                          NULL);                // creation parameters

   //make sure the window creation has gone OK
   if(!hWnd)
   {
     MessageBox(NULL, "CreateWindowEx Failed!", "Error!", 0);
   }

   //make the window visible
   ShowWindow (hWnd, iCmdShow);
   UpdateWindow (hWnd);
     
   // enter the message loop
   bool bDone = false;

   MSG msg;

   while(!bDone)
   {
          
     while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
     {
       if( msg.message == WM_QUIT ) 
       {
         // Stop loop if it's a quit message
         bDone = true;
       } 

       else 
       {
         TranslateMessage( &msg );
         DispatchMessage( &msg );
       }
     }

     if (!g_Controller->Finished())
     {
       if (!g_Controller->Train())
       {
         bDone = true; //quit if there is a problem
       }
      
       //this will call WM_PAINT which will render the map
       InvalidateRect(hWnd, NULL, TRUE);
       UpdateWindow(hWnd);
     }
            
   }//end while

  delete g_Controller;

  UnregisterClass( g_szWindowClassName, winclass.hInstance );

  return msg.wParam;
}


