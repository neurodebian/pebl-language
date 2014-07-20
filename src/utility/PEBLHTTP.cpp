#include "PEBLHTTP.h"


#ifdef PEBL_WIN32
#include  <winsock2.h>
#endif

#ifdef PEBL_HTTP

#include "PError.h"
#include <stdio.h>
#include "../base/PList.h"
#include "../base/PComplexData.h"
#include "../utility/rc_ptrs.h"

void http_begin_cb( const happyhttp::Response* r,
			   void* userdata )
{
  //I don't think any of this is needed:
  PEBLHTTP* http = (PEBLHTTP*)(userdata);
  //  FILE * filestream = http->GetFileObject();
   printf( "BEGIN (%d %s)\n", r->getstatus(), r->getreason() );
   http->SetByteCount(0);
   http->SetStatus(r->getstatus());
   http->SetReason(std::string(r->getreason()));

}

 void http_getdata_cb( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n )
{

  PEBLHTTP* http = (PEBLHTTP*) (userdata);
  FILE * filestream = http->GetFileObject();

  //FILE * filestream = (FILE*)userdata;

  //  std::cout << http->GetByteCount() << std::endl;

  //(filestream) << data;
  // fputs(data,filestream);
  //  fwrite( data,1,n,::stdout);
  fwrite( data,1,n, filestream);
  //std::cout << data << std::endl;
  //std::cout << "B\n";
  http->SetByteCount(http->GetByteCount()+n);
}

 void http_complete_cb( const happyhttp::Response* r, void* userdata )
{
  //. PEBLHTTP* http = (PEBLHTTP*) userdata;
 //  FILE * filestream = http->GetFileObject();
  //  fclose(filestream);

   //printf( "COMPLETE (%d bytes)\n", http->GetByteCount() );
   //printf( "COMPLETE (%d bytes)\n", 33);

}

// These save the http retrieved to a s strstream for later use,
// rather than a file.
//

void http_begin_cb2( const happyhttp::Response* r,
			   void* userdata )
{
  //I don't think any of this is needed:
  PEBLHTTP* http = (PEBLHTTP*)(userdata);
  //  FILE * filestream = http->GetFileObject();

  //printf( "BEGIN (%d %s)\n", r->getstatus(), r->getreason() );
  http->SetStatus(r->getstatus());
  http->SetReason(std::string(r->getreason()));
  http->SetByteCount(0);

}

 void http_getdata_cb2( const happyhttp::Response* r, void* userdata,
			const unsigned char* data, int n )
{

  PEBLHTTP* http = (PEBLHTTP*) (userdata);
  //FILE * filestream = http->GetFileObject();
  //FILE * filestream = (FILE*)userdata;

  std::string * text = http->GetTextObject();
  text->append((const char*)data, n);

  //  std::cout << "tmp text:" << *text << std::endl;

  http->SetByteCount(http->GetByteCount()+n);
}

 void http_complete_cb2( const happyhttp::Response* r, void* userdata )
{
   //PEBLHTTP* http = (PEBLHTTP*) userdata;
   //   std::string * text = http->GetTextObject();
   //  FILE * filestream = http->GetFileObject();
   //  fclose(filestream);
   //printf( "COMPLETE (%d bytes)\n", http->GetByteCount() );
   //printf( "COMPLETE (%d bytes)\n", 33);

}





PEBLHTTP::PEBLHTTP(Variant host)
{
  mHost = host;
#ifdef WIN32
    WSAData wsaData;
    int code = WSAStartup(MAKEWORD(1, 1), &wsaData);
if( code != 0 )
{
PError::SignalFatalError(Variant("Unable to start http library.") + Variant(code));
}
#endif //WI

}


PEBLHTTP::~PEBLHTTP()
{
  if(mText)
      delete mText;
  mText = NULL;
}


//This gets an http url and saves it to the specified file.
//this assumes you are getting a binary-formatted file.
int PEBLHTTP::GetHTTPFile(Variant  filename,
			   Variant savename)
{

    // simple simple GET
  happyhttp::Connection conn(mHost.GetString().c_str(), 80 );
  //we should set binary/text here too?
  //such as png, gif, jpg, .wav, .ogg, .mp3, etc?



  mFile = fopen(savename.GetString().c_str(),"wb");

  //Somehow, we need to 'prime' the file, or else it comes out
  //of the void* cast as NULL.
  fwrite( "",1,0,mFile);

  conn.setcallbacks( http_begin_cb,
		     http_getdata_cb,
		     http_complete_cb, this);



  try
    {

      conn.request( "GET", filename.GetString().c_str(), 0, 0,0 );
      while( conn.outstanding() )
	{
	  //std::cout << "+" << std::flush;
	  conn.pump();
	     }

      fclose(mFile);
      return mStatus;

    }
  catch( happyhttp::Wobbly& e )
    {
	  char s[300];
	  sprintf(s,"Exception:\n%s\n", e.what() );
	  PError::SignalWarning(s);
	  fclose(mFile);
	  return 0;  //mstatus may not exist here
    }

}



//This gets an http url and saves it to the specified file.
//this assumes you are getting a binary-formatted file.
int PEBLHTTP::GetHTTPText(Variant  filename)
{

    // simple simple GET
  happyhttp::Connection conn(mHost.GetString().c_str(), 80 );
  //we should set binary/text here too?
  //such as png, gif, jpg, .wav, .ogg, .mp3, etc?


  mText = new std::string;

  conn.setcallbacks( http_begin_cb2,
		     http_getdata_cb2,
		     http_complete_cb2, this);

       try
	 {

	   conn.request( "GET", filename.GetString().c_str(), 0, 0,0 );

	   while( conn.outstanding() )
	     {
	       //std::cout << "+" << std::flush;
	       conn.pump();
	     }

	   return mStatus;

	 }
       catch( happyhttp::Wobbly& e )
	{
	  cout << "Wobbly caught\n";
	  char s[300];
	  sprintf(s,"Exception:\n%s\n", e.what() );
	  PError::SignalWarning(s);
	  return 0;  //mstatus may not exist here
	}
}


int PEBLHTTP::PostHTTP(Variant name,
			Variant headersx,
			Variant bodyx)
//Variant savename)
{


  //mFile = fopen("tmp.html","wb");
  //  fwrite( "",1,0,mFile);

  mText = new std::string;


  //headersx is a variant-list, we need to create a const char* list
  //to contain it (with a 0 at the end).
   PError::AssertType(headersx, PEAT_LIST, "PostHTTP headers must be a list");


   cout << headersx.GetComplexData() << std::endl;
   //cout << (headersx.GetComplexData())->GetObject().get() << std::endl;
    PList * dataList = (PList*)(headersx.GetComplexData()->GetPEBLObject().get());
   //PComplexData * pcd = (headersx.GetComplexData());
   //counted_ptr<PEBLObjectBase> pl = pcd->GetObject();
   //PList * dataList = pl.get();
   //(PList*)(pcd->GetObject().get());
  const char** headers = (const char**)malloc(sizeof(const char*) * (dataList->Length()+1));

  std::vector<Variant>::iterator p1 = dataList->Begin();
  std::vector<Variant>::iterator p1end = dataList->End();

  int i = 0;

  while(p1 != p1end)
    {

//      headers[i] = strdupa((*p1).GetString().c_str());
       headers[i]= strdup((*p1).GetString().c_str());
      p1++;
      i++;
    }

  headers[i] = NULL;


  // simple POST command
  happyhttp::Connection conn(mHost.GetString().c_str(), 80 );

  //  mFile = fopen(savename.GetString().c_str(),"wb");

  //Somehow, we need to 'prime' the file, or else it comes out
  //of the void* cast as NULL.
  //  fwrite( "",1,0,mFile);


  conn.setcallbacks( http_begin_cb2,
		     http_getdata_cb2,
		     http_complete_cb2, this);



  std::string body1 = bodyx.GetString();
  const unsigned char* body = (unsigned char*)(body1.c_str());


  unsigned int l = strlen(bodyx.GetString().c_str());

  //  std::cout <<"Starting POST pump\n";

  try
    {
      conn.request( "POST",
		    name.GetString().c_str(),
		    headers,
		    body,l);

      while( conn.outstanding() )
	{

	  conn.pump();
	}
      //      fclose(mFile);
      //      mFile = NULL;
    for(int ii = 0; ii<(i-1);ii++)
      {
         if(headers[ii]) free(&headers[ii]);

      }


      return mStatus;
    }
  catch( happyhttp::Wobbly& e )
    {
      char s[300];
      sprintf(s,"Exception:\n%s\n", e.what() );
      PError::SignalWarning(s);


      //      fclose(mFile);
      //      mFile = NULL;
      return mStatus;
    }
}

#endif
