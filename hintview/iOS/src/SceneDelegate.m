//
//  SceneDelegate.m
//  iOSHintView
//
//  Created by Martin Ruckert on 10.10.22.
//

#import "SceneDelegate.h"
#import "ViewController.h"
#include "main.h"

@interface SceneDelegate ()

@end

@implementation SceneDelegate


- (void)scene:(UIScene *)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions {
    // Use this method to optionally configure and attach the UIWindow `window` to the provided UIWindowScene `scene`.
    // If using a storyboard, the `window` property will automatically be initialized and attached to the scene.
    // This delegate does not imply the connecting scene or session are new (see `application:configurationForConnectingSceneSession` instead).
    // Used to start HintView with an URL from the finder if not yet running
    NSSet *c = connectionOptions.URLContexts;
        if(c && [c count] > 0)
        { NSURL *url = ((UIOpenURLContext*)[[c allObjects] firstObject]).URL;
          NSLog(@"Scene will connect with url %@", url);
          open_file(url);
        }
}


- (void)scene:(UIScene *)scene openURLContexts:(nonnull NSSet<UIOpenURLContext *> *)URLContexts
API_AVAILABLE(ios(13.0)){
    // Used if clicking in Finder
    NSURL *url = [[URLContexts allObjects] firstObject].URL;
    if (url!=nil)
    {
        NSLog(@"Scene open url context %@", url);
        open_file(url);
    }
    
   
}
- (void)sceneDidDisconnect:(UIScene *)scene {
    // Called as the scene is being released by the system.
    // This occurs shortly after the scene enters the background, or when its session is discarded.
    // Release any resources associated with this scene that can be re-created the next time the scene connects.
    // The scene may re-connect later, as its session was not necessarily discarded (see `application:didDiscardSceneSessions` instead).
    NSLog(@"Disconnect");
    set_preferences();
}


- (void)sceneDidBecomeActive:(UIScene *)scene {
    // Called when the scene has moved from an inactive state to an active state.
    // Use this method to restart any tasks that were paused (or not yet started) when the scene was inactive.
 }


- (void)sceneWillResignActive:(UIScene *)scene {
    // Called when the scene will move from an active state to an inactive state.
    // This may occur due to temporary interruptions (ex. an incoming phone call).
    NSLog(@"Resign active");
   }


- (void)sceneWillEnterForeground:(UIScene *)scene {
    // Called as the scene transitions from the background to the foreground.
    // Use this method to undo the changes made on entering the background.
 }


- (void)sceneDidEnterBackground:(UIScene *)scene {
    // Called as the scene transitions from the foreground to the background.
    // Use this method to save data, release shared resources, and store enough scene-specific state information
    // to restore the scene back to its current state.
    NSLog(@"Enter background");
    set_preferences();
   }

- (void)windowScene:(UIWindowScene *)windowScene
performActionForShortcutItem:(UIApplicationShortcutItem *)shortcutItem
  completionHandler:(void (^)(BOOL succeeded))completionHandler
{   NSLog(@"Not used perform action");
}

- (void)openURL:(NSURL *)url
        options:(UISceneOpenExternalURLOptions *)options
completionHandler:(void (^)(BOOL success))completion
{
    NSLog(@"Not used openUrl:");
}



@end
