#include <stdio.h>
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AppKit/AppKit.h>

int main(int argc, char *argv[])
{

  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  [NSApplication sharedApplication];

  AppDelegate *appDelegate = [[AppDelegate alloc] init];
  [NSApp setDelegate:appDelegate];
  [NSApp run];
  [pool release];
  return 0;
}