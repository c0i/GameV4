
// https://stackoverflow.com/a/7307150/5443510

#ifndef SimulatorLog_h
#define SimulatorLog_h

#import <Foundation/Foundation.h>
 
#ifdef DEBUG

#define NSLog( s, ... ) [SimulatorLog log:[NSString stringWithFormat:(s), ##__VA_ARGS__]]

#endif

@interface SimulatorLog : NSObject

+ (void)setRedirectNSLogEnabled:(BOOL)redirect;
+ (void)log:(NSString *)format, ...;
//+ (void)log:(NSString*)fileName method:(NSString*)method lineNr:(NSNumber*)lineNr text:(NSString *)format, ...;

@end

#endif /* SimulatorLog_h */
