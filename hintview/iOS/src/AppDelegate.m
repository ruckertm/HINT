//
//  AppDelegate.m
//  iOSHintView
//
//  Created by Martin Ruckert on 10.10.22.
//

#import "AppDelegate.h"
#include "error.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "hint.h"
#include "hrender.h"
#include "main.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application
willFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions
{   NSLog(@"App will finish launch %@",launchOptions);
    if (launchOptions!=nil)
    {
        NSURL *url = [launchOptions objectForKey:UIApplicationLaunchOptionsURLKey];
        NSLog(@"App will finish lauching with url %@", url);
    }
        
    
    return YES;
}

- (void)application:(UIApplication *)application
performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem
  completionHandler:(void (^)(BOOL succeeded))completionHandler
{
    NSLog(@"App action for shortcut");
}

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{ NSLog(@"App did finish launch options %@", launchOptions);
    if (launchOptions!=nil)
    {
        NSURL *url = [launchOptions objectForKey:UIApplicationLaunchOptionsURLKey];
        NSLog(@"App did finish lauching with url %@", url);
          }
        
    return YES;
}

- (BOOL)canOpenURL:(NSURL *)url;
{    NSLog(@"App can open url");
      return YES;
}

- (void)openURL:(NSURL *)url
        options:(NSDictionary<UIApplicationOpenExternalURLOptionsKey, id> *)options
completionHandler:(void (^)(BOOL success))completion
{ NSLog(@"App open URL");
  }

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options
{ NSLog(@"App open URL with options %@", options);
  return YES;
}


-(BOOL)application:(UIApplication *)application
           openURL:(NSURL *)url
 sourceApplication:(NSString *)sourceApplication
        annotation:(id)annotation
{ NSLog(@"App open url with source %@", url);
#if 0
    if (url!=nil && [url isFileURL])
        hint_error("Open",[[url path] UTF8String]);
    else
        hint_error("Dont open", [[url path] UTF8String]);
#endif
    return YES;
}


#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    // Called when a new scene session is being created.
    // Use this method to select a configuration to create the new scene with.
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}


- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
    // Called when the user discards a scene session.
    // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
    // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
}



@end
