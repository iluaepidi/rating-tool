var widgetStrings = (function () {
    
  var _values = {
      TITLE : Drupal.t("Customer reviews"),
      "CUSTOMER REVIEW" : Drupal.t("Customer review"),
      "CUSTOMER REVIEWS" : Drupal.t("Customer reviews"),
      "OUT OF" : Drupal.t("out of"),
      CREATE : Drupal.t("Write your review"),
      READ : Drupal.t("Read"),
      UPDATE : Drupal.t("Edit your review"),
      DELETE : Drupal.t("Delete your review"),
      REPLY : Drupal.t("Respond to review"),
      SEND : Drupal.t("Send"),
      BACK: Drupal.t("Back"),
      CANCEL : Drupal.t("Cancel"),
      COMMENTS : Drupal.t("Comments"),
      COMMENT: Drupal.t("Comment"),
      STARS: Drupal.t("Stars"),
      STAR: Drupal.t("Star"),
      ABOUT: Drupal.t("About"),
      CONFIRM : Drupal.t("Confirm"),
      "CONFIRM ACTION" : Drupal.t("Confirm action"),
      "DELETE CONFIRM" : Drupal.t("Do you really want to delete this comment?"),
      "FLAG CONFIRM" : Drupal.t("Do you really want to flag this comment?"),
      "MORE COMMENTS" : Drupal.t("More reviews"),
      "LESS COMMENTS" : Drupal.t("Less reviews"),
      "LABEL REVIEW INTRO" : Drupal.t("Your review of this product"),
      "LABEL STAR RATING" : Drupal.t("Your overall rating of this product"),
      "LABEL REVIEW TITLE" : Drupal.t("Title of your review"),
      "LABEL REVIEW BODY" : Drupal.t("Write your review here"),
      "MESSAGE REVIEW OK" : Drupal.t("Thank you! Review submitted."),
      "EDIT REPLY"        : Drupal.t("Edit reply"),
      "DELETE REPLY"      :Drupal.t( "Delete reply"),
      "EMPTY FIELDS" : Drupal.t("Please write a title and comment"),
      "FLAG CONTENT" : Drupal.t("Flag content"),
      "FLAGED CONTENT" : Drupal.t("Flaged content"),
      "LIKE CONTENT" : Drupal.t("Like comment"),
      "LIKED CONTENT" : Drupal.t("Likes")
  };
  // var _locale = "en-UK";
  var _locale = "en-UK";

  // Explicitly reveal public pointers to the private functions 
  // that we want to reveal publicly

   var value = function(key) {
       return _values[key];
   };
   var locale = function(){return _locale};
  
  return {
    value: value,
    locale: locale
  }
})();