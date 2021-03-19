
#import "SimulatorLog.h"

static BOOL SimulatorLog_redirect = NO;
@implementation SimulatorLog

+ (void)setRedirectNSLogEnabled:(BOOL)redirect
{
    SimulatorLog_redirect = redirect;
}

//+(void)log:(NSString*)fileName method:(NSString*)method lineNr:(NSNumber*)lineNr text:(NSString *)format, ...
+(void)log:(NSString *)format, ...
{
    
    // Type to hold information about variable arguments.
    va_list ap;

    // Initialize a variable argument list.
    va_start (ap, format);

    // NSLog only adds a newline to the end of the NSLog format if
    // one is not already there.
    // Here we are utilizing this feature of NSLog()
    if (![format hasSuffix: @"\n"])
    {
        format = [format stringByAppendingString: @"\n"];
    }

    NSString *body = nil;
    if (SimulatorLog_redirect)
    {
         body = [[NSString alloc] initWithFormat:format arguments:ap];
    }

    // End using variable argument list.
    va_end (ap);

    NSLogv(format, ap);
    
    // @bug: !!stderr, can not work!!
    if (SimulatorLog_redirect)
    {
        fprintf(stdout, "%s", [body UTF8String]);
        fflush(stdout);
        [body release];
    }
}

@end

