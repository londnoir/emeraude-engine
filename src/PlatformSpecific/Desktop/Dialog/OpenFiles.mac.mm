#include "OpenFiles.hpp"

#if IS_MACOS

/* Third-party inclusions. */
#import <OpenGL/OpenGL.h>
#import <OpenGL/CGLMacro.h>
#import <AppKit/AppKit.h>

/* Local inclusions. */
#include "Window.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
	bool
	OpenFiles::execute (Window * /*window*/) noexcept
	{
        @autoreleasepool
        {
            [NSApplication sharedApplication];
            [NSApp setActivationPolicy:NSApplicationActivationPolicyAccessory];

            NSString * title = [NSString stringWithCString:this->title().c_str()
            encoding:[NSString defaultCStringEncoding]];

            NSOpenPanel * openPanel = [NSOpenPanel openPanel];

            [openPanel setCanChooseFiles:YES];
            [openPanel setCanChooseDirectories:NO];
            [openPanel setAllowsMultipleSelection:YES];
            [openPanel setTitle:title];

            NSMutableArray * file_types_list = [NSMutableArray array];
            NSMutableArray * filter_names = [NSMutableArray array];
            NSMutableOrderedSet * file_type_set = [NSMutableOrderedSet orderedSetWithCapacity:m_extensionFilters.size()];

            for ( auto & filter : m_extensionFilters )
            {
                [filter_names addObject:@(filter.first.c_str())];

                for ( std::string & ext : filter.second )
                {
                    // From electron :
                    // macOS is incapable of understanding multiple file extensions,
                    // so we need to tokenize the extension that's been passed in.
                    // We want to err on the side of allowing files, so we pass
                    // along only the final extension ('tar.gz' => 'gz').
                    auto pos = ext.rfind('.');

                    if ( pos != std::string::npos )
                    {
                        ext.erase(0, pos + 1);
                    }

                    [file_type_set addObject:@(ext.c_str())];
                }
            }
            [file_types_list addObject:[file_type_set array]];

            // Passing empty array to setAllowedFileTypes will cause exception.
            NSArray * file_types = nil;
            NSUInteger count = [file_types_list count];

            if ( count > 0 )
            {
                file_types = [[file_types_list objectAtIndex:0] allObjects];

                // If we meet a '*' file extension, we allow all the file types and no
                // need to set the specified file types.
                if ( [file_types count] == 0 || [file_types containsObject:@"*"] )
                {
                    file_types = nil;
                }
            }
            [openPanel setAllowedFileTypes:file_types];

            // TODO: Format picker not yet implemented, macOS doesnt support it natively.
            // To create it like electron see : https://github.com/electron/electron/blob/main/shell/browser/ui/file_dialog_mac.mm#L133
            [openPanel setLevel:CGShieldingWindowLevel()];
            NSInteger result = [openPanel runModal];

            if ( result == NSModalResponseOK )
            {
                NSArray * URLs = [openPanel URLs];

                for ( NSURL * url in URLs )
                {
                    NSString * filePath = [url path];
                    m_filePaths.emplace_back([filePath UTF8String]);
                }
            }
            else
            {
                NSLog(@"File picker canceled");
            }
        }  // end of autorelease pool.

        return true;
	}
}

#endif
