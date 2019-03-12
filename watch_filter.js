
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Filter used to determine what files and directories are watched.
//  https://www.npmjs.com/package/watch
//
////////////////////////////////////////////////////////////////////////////////

module.exports = function ( path )
{
  // Only forward slashes.
  path = path.replace ( "\\", "/" );

  // Reject these directories.
  if ( ( path.indexOf ( ".git" ) >= 0 ) ||
       ( path.indexOf ( "node_modules" ) >= 0 ) ||
       ( path.indexOf ( "build" ) >= 0 ) ||
       ( path.indexOf ( "external" ) >= 0 ) )
  {
    return false;
  }

  const file = path.split ( "/" ).pop();

  // Reject these files.
  if ( ( file == ".DS_Store" ) ||
       ( file == ".travis.yml" ) ||
       ( file == "Config.h" ) ||
       ( file == "License.md" ) ||
       ( file == "npm-shrinkwrap.json" ) ||
       ( file == "ReadMe.md" ) ||
       ( file == "Version.h" ) ||
       ( file == "watch_filter.js" ) )
  {
    return false;
  }

  // Uncomment to see approved files.
  // console.log ( "Approving:", path );

  // If we get to here then the file or directory is approved.
  return true;
};
