
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
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

  path = path.split ( "/" ).pop();

  // Reject these files.
  if ( ( path == ".DS_Store" ) ||
       ( path == ".travis.yml" ) ||
       ( path == "Config.h" ) ||
       ( path == "License.md" ) ||
       ( path == "npm-shrinkwrap.json" ) ||
       ( path == "ReadMe.md" ) ||
       ( path == "Version.h" ) ||
       ( path == "watch_filter.js" ) )
  {
    return false;
  }

  // Uncomment to see approved files.
  // console.log ( "Approving:", path );

  // If we get to here then the file or directory is approved.
  return true;
};
