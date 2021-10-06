/* --------------------------------------------------------------------------
   Node++ Web App
   Jurek Muszynski
   nodepp.org
-----------------------------------------------------------------------------
   Hello World Sample Node++ Web Application
-------------------------------------------------------------------------- */


#include "npp.h"


/* --------------------------------------------------------------------------------
   Called after parsing HTTP request header
   ------------------------------
   This is the main entry point for a request
   ------------------------------
   Response status will be 200 by default
   Use RES_STATUS() if you want to change it
-------------------------------------------------------------------------------- */
void npp_app_main(int ci)
{
    if ( REQ("") )  // landing page
    {
        OUT_HTML_HEADER;

        OUT("<h1>%s</h1>", NPP_APP_NAME);
        OUT("<h2>Welcome to my web app!</h2>");

        if ( REQ_DSK )
            OUT("<p>You're on desktop.</p>");
        else  /* REQ_MOB */
            OUT("<p>You're on the phone.</p>");

        OUT("<p>Click <a href=\"welcome\">here</a> to try my welcoming bot.</p>");

        OUT_HTML_FOOTER;
    }
    else if ( REQ("welcome") )  // welcoming bot
    {
        OUT_HTML_HEADER;
        OUT("<h1>%s</h1>", NPP_APP_NAME);

        OUT("<p>Please enter your name:</p>");
        OUT("<form action=\"welcome\"><input name=\"firstname\" autofocus> <input type=\"submit\" value=\"Run\"></form>");

        QSVAL qs_firstname;   // query string value

        if ( QS("firstname", qs_firstname) )    // if present, bid welcome
            OUT("<p>Welcome %s, my dear friend!</p>", qs_firstname);

        OUT("<p><a href=\"/\">Back to landing page</a></p>");

        OUT_HTML_FOOTER;
    }
    else  // page not found
    {
        RES_STATUS(404);
    }
}


/* --------------------------------------------------------------------------------
   Called when application starts
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will stop booting process,
   npp_app_done() will be called and application will be terminated
-------------------------------------------------------------------------------- */
bool npp_app_init(int argc, char *argv[])
{
    return true;
}


/* --------------------------------------------------------------------------------
   Called when new anonymous session is starting
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will cause the session to be closed
   and npp_app_session_done() will be called
   Response status will be set to 500
-------------------------------------------------------------------------------- */
bool npp_app_session_init(int ci)
{
    return true;
}


#ifdef NPP_USERS
/* --------------------------------------------------------------------------------
   ******* Only for USERS *******
   ------------------------------
   Called after successful authentication (using password or cookie)
   when user session is upgraded from anonymous to logged in
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will cause the session to be downgraded back to anonymous
   and npp_app_user_logout() will be called
-------------------------------------------------------------------------------- */
bool npp_app_user_login(int ci)
{
    return true;
}


/* --------------------------------------------------------------------------------
   ******* Only for USERS *******
   ------------------------------
   Called when downgrading logged in user session to anonymous
   Application session data (SESSION_DATA) will be zero-ed as well,
   unless NPP_KEEP_SESSION_DATA_ON_LOGOUT is defined
-------------------------------------------------------------------------------- */
void npp_app_user_logout(int ci)
{
}
#endif  /* NPP_USERS */


/* --------------------------------------------------------------------------------
   Called when closing anonymous session
   After calling this the session memory will be zero-ed
-------------------------------------------------------------------------------- */
void npp_app_session_done(int ci)
{
}


/* --------------------------------------------------------------------------------
   Called when application shuts down
-------------------------------------------------------------------------------- */
void npp_app_done()
{
}
