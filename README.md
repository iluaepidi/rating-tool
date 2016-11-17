# rating-tool

In order to install Drupal rating tool you need to dowload  zip file containing module files.

You can install the module as you install any other modules. Uncompress and copy it to your site modules folder. You can install it using Drupal interface.
 
P4A server part has following dependencies:
- Ctools
- Views

P4A Client part needs at least a jQuery 1.7 so you need to install jQuery Update module.

Once module is installed you may activate them in modules section in Drupal  adminsitration panel.

Module contains three submodules. One for the API and other two for server and client part of the module.
 
Rating API is required in order to install client and server part.

Once modules are installed yuo need to configure them in the configuration section in your Drupal site.

Te most importsnt setting is the P4A server. Iif server is installed in the same Drupal the setting shold be [your server]/widget/. Note the final slash.

Others settings are self explained.  Order comments by likes or by date.  Number of comments that should be showed in comments list. Number of aproved comments for autoaprove and number of flags in a comment for auto unaprove comment.

Server part contains the database tables and logic to store and serve the ratings and comments as well administrative interface for comments. As part of installation module will create two new roles in Drupal. Vendor and comment moderator.

For enter in administrative interface you should go to [your_server]/widget/comments/moderation
 
Remember that before you can use this administrative interface you have to activate the views (disabled after installation) related with Rating Tool. To do this go to structure, views and in the list of existing views activate two views named P4A, comment detail and P4A, comments moderation.
 
P4A Client part installs two blocks in Drupal blocks sections that you can place in any region.
 
And you should configure the paths for the visibility of the blocks in your site.