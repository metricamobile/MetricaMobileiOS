

#import <Foundation/Foundation.h>

#define BWMetricaMobileLog(fmt, ...) do { if([BWMetricaMobileManager sharedMetricaMobileManager].isLoggingEnabled) { NSLog((@"[MetricaMobileLib] %s/%d " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__); }} while(0)

#define kMetricaMobileBundleName @"MetricaMobile.bundle"

NSBundle *metricaMobileBundle(void);
NSString *BWMetricaMobileLocalize(NSString *stringToken);

//#define BWMetricaMobileLocalize(StringToken) NSLocalizedStringFromTableInBundle(StringToken, @"MetricaMobile", metricaMobileBundle(), @"")

// flags if the crashlog analyzer is started. since this may theoretically crash we need to track it
#define kMetricaMobileKitAnalyzerStarted @"MetricaMobileKitAnalyzerStarted"

// flags if the MetricaMobileKit is activated at all
#define kMetricaMobileKitActivated @"MetricaMobileKitActivated"

// flags if the crashreporter should automatically send crashes without asking the user again
#define kAutomaticallySendCrashReports @"AutomaticallySendCrashReports"

// stores the set of crashreports that have been approved but aren't sent yet
#define kApprovedCrashReports @"ApprovedCrashReports"

// Notification message which MetricaMobileManager is listening to, to retry sending pending crash reports to the server
#define BWMetricaMobileNetworkBecomeReachable @"NetworkDidBecomeReachable"

typedef enum MetricaMobileKitAlertType {
  MetricaMobileKitAlertTypeSend = 0,
  MetricaMobileKitAlertTypeFeedback = 1,
} CrashAlertType;

typedef enum CrashReportStatus {
  // The status of the crash is queued, need to check later (MetricaMobileApp)
  CrashReportStatusQueued = -80,
  
  // This app version is set to discontinued, no new crash reports accepted by the server
  CrashReportStatusFailureVersionDiscontinued = -30,
  
  // XML: Sender version string contains not allowed characters, only alphanumberical including space and . are allowed
  CrashReportStatusFailureXMLSenderVersionNotAllowed = -21,
  
  // XML: Version string contains not allowed characters, only alphanumberical including space and . are allowed
  CrashReportStatusFailureXMLVersionNotAllowed = -20,
  
  // SQL for adding a symoblicate todo entry in the database failed
  CrashReportStatusFailureSQLAddSymbolicateTodo = -18,
  
  // SQL for adding crash log in the database failed
  CrashReportStatusFailureSQLAddCrashlog = -17,
  
  // SQL for adding a new version in the database failed
  CrashReportStatusFailureSQLAddVersion = -16,
	
  // SQL for checking if the version is already added in the database failed
  CrashReportStatusFailureSQLCheckVersionExists = -15,
	
  // SQL for creating a new pattern for this bug and set amount of occurrances to 1 in the database failed
  CrashReportStatusFailureSQLAddPattern = -14,
	
  // SQL for checking the status of the bugfix version in the database failed
  CrashReportStatusFailureSQLCheckBugfixStatus = -13,
	
  // SQL for updating the occurances of this pattern in the database failed
  CrashReportStatusFailureSQLUpdatePatternOccurances = -12,
	
  // SQL for getting all the known bug patterns for the current app version in the database failed
  CrashReportStatusFailureSQLFindKnownPatterns = -11,
	
  // SQL for finding the bundle identifier in the database failed
  CrashReportStatusFailureSQLSearchAppName = -10,
	
  // the post request didn't contain valid data
  CrashReportStatusFailureInvalidPostData = -3,
	
  // incoming data may not be added, because e.g. bundle identifier wasn't found
  CrashReportStatusFailureInvalidIncomingData = -2,
	
  // database cannot be accessed, check hostname, username, password and database name settings in config.php
  CrashReportStatusFailureDatabaseNotAvailable = -1,
	
  CrashReportStatusUnknown = 0,
	
  CrashReportStatusAssigned = 1,
	
  CrashReportStatusSubmitted = 2,
	
  CrashReportStatusAvailable = 3,
} CrashReportStatus;

// This protocol is used to send the image updates
@protocol BWMetricaMobileManagerDelegate <NSObject>

@optional

// Return the userid the crashreport should contain, empty by default
-(NSString *) crashReportUserID;

// Return the contact value (e.g. email) the crashreport should contain, empty by default
-(NSString *) crashReportContact;

// Return the description the crashreport should contain, empty by default. The string will automatically be wrapped into <[DATA[ ]]>, so make sure you don't do that in your string.
-(NSString *) crashReportDescription;

// Invoked when the internet connection is started, to let the app enable the activity indicator
-(void) connectionOpened;

// Invoked when the internet connection is closed, to let the app disable the activity indicator
-(void) connectionClosed;

// Invoked before the user is asked to send a crash report, so you can do additional actions. E.g. to make sure not to ask the user for an app rating :) 
-(void) willShowSubmitCrashReportAlert;

// Invoked after the user did choose to send crashes always in the alert 
-(void) userDidChooseSendAlways;

@end


@interface BWMetricaMobileManager : NSObject <NSXMLParserDelegate> {
  NSString *_submissionURL;
  
  id <BWMetricaMobileManagerDelegate> _delegate;
  
  BOOL _loggingEnabled;
  BOOL _showAlwaysButton;
  BOOL _feedbackActivated;
  BOOL _autoSubmitCrashReport;
  
  BOOL _didCrashInLastSession;
  
  NSString *_appIdentifier;
  
  NSString *_feedbackRequestID;
  float _feedbackDelayInterval;
  
  NSMutableString *_contentOfProperty;
  CrashReportStatus _serverResult;
  
  int _analyzerStarted;
  NSString *_crashesDir;
	
  BOOL _crashIdenticalCurrentVersion;
  BOOL _crashReportActivated;
  
  NSMutableArray *_crashFiles;
	
  NSMutableData *_responseData;
  NSInteger _statusCode;
  
  NSURLConnection *_urlConnection;
  
  NSData *_crashData;
  
  NSString *_languageStyle;
  BOOL _sendingInProgress;
    //Stadistics: Start
    double unsentSessionLength;
	NSTimer *timer;
	double lastTime;
	BOOL isSuspended;
    //End Stadistics
}

+ (BWMetricaMobileManager *)sharedMetricaMobileManager;
- (void)start:(NSString *)appKey withHost:(NSString *)appHost;
- (void)start:(NSString *)appKey;
// submission URL defines where to send the crash reports to (required)
@property (nonatomic, retain) NSString *submissionURL;

// delegate is optional
@property (nonatomic, assign) id <BWMetricaMobileManagerDelegate> delegate;

///////////////////////////////////////////////////////////////////////////////////////////////////
// settings

// if YES, states will be logged using NSLog. Only enable this for debugging!
// if NO, nothing will be logged. (default)
@property (nonatomic, assign, getter=isLoggingEnabled) BOOL loggingEnabled;

// nil, using the default localization files (Default)
// set to another string which will be appended to the MetricaMobile localization file name, "Alternate" is another provided text set
@property (nonatomic, retain) NSString *languageStyle;

// if YES, the user will get the option to choose "Always" for sending crash reports. This will cause the dialog not to show the alert description text landscape mode! (default)
// if NO, the dialog will not show a "Always" button
@property (nonatomic, assign, getter=isShowingAlwaysButton) BOOL showAlwaysButton;

// if YES, the user will be presented with a status of the crash, if known
// if NO, the user will not see any feedback information (default)
@property (nonatomic, assign, getter=isFeedbackActivated) BOOL feedbackActivated;

// if YES, the crash report will be submitted without asking the user
// if NO, the user will be asked if the crash report can be submitted (default)
@property (nonatomic, assign, getter=isAutoSubmitCrashReport) BOOL autoSubmitCrashReport;

// will return if the last session crashed, to e.g. make sure a "rate my app" alert will not show up
@property (nonatomic, readonly) BOOL didCrashInLastSession;

// If you want to use MetricaMobileApp instead of your own server, this is required
@property (nonatomic, retain) NSString *appIdentifier;

@end
