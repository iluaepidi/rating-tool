<h1><span class="widgetStrings">TITLE</span></h1>
<div class="widget_stars" id="widget_stars_comments_part">
    <p id="review_stars"></p>
    <div id="histogram" class="">
        <table>
            <tr>
                <th><a href="#listComments">5 <span class="visuallyhidden"><span class="widgetStrings">STARS</span></span>&#9733;</a></th>
                <td></td>
            </tr>
            <tr>
                <th><a href="#listComments">4 <span class="visuallyhidden"><span class="widgetStrings">STARS</span></span>&#9733;</a></th>
                <td></td>
            </tr>
            <tr>
                <th><a href="#listComments">3 <span class="visuallyhidden"><span class="widgetStrings">STARS</span></span>&#9733;</a></th>
                <td></td>
            </tr>
            <tr>
                <th><a href="#listComments">2 <span class="visuallyhidden"><span class="widgetStrings">STARS</span></span>&#9733;</a></th>
                <td></td>
            </tr>
            <tr>
                <th><a href="#listComments">1 <span class="visuallyhidden"><span class="widgetStrings">STAR</span></span>&#9733;</a></th>
                <td></td>
            </tr>
        </table>
    </div>
    <p class="about"><a href="#about" class="inline"><span class="widgetStrings">ABOUT</span></a></p>
    <div id="widget_content" class="widget_content">
        
        <div id="listComments" class="comments">
            <ul id="widget_comments_ul">

            </ul>
        </div>
        
        <p class="alignright"><a id="morecomments" href="#" class="less"><span class="widgetStrings">LESS COMMENTS</span></a></p>
            
        <div id="provideoyourrate" style="display:none;">
            <h2><span class="widgetStrings">LABEL REVIEW INTRO</span></h2>
            <p><span class="widgetStrings">LABEL STAR RATING</span></p>
            <form action="">
                <p class="widget_categorization widget_stars_rate">
                    <input id="widget_stars_rate_1" type="radio" name="widget_stars_rate" value="1" class="visuallyhidden" checked="checked">
                    <label for="widget_stars_rate_1" class="widget_label"><span class="visuallyhidden">1 <span class="widgetStrings">STAR</span></span><span class="spanstar">&#9733</span></label>

                    <input id="widget_stars_rate_2" type="radio" name="widget_stars_rate" value="2" class="visuallyhidden">
                    <label for="widget_stars_rate_2" class="widget_label"><span class="visuallyhidden">2 <span class="widgetStrings">STARS</span></span><span class="spanstar">&#9733</span></label>

                    <input id="widget_stars_rate_3" type="radio" name="widget_stars_rate" value="3" class="visuallyhidden">
                    <label for="widget_stars_rate_3" class="widget_label"><span class="visuallyhidden">3 <span class="widgetStrings">STARS</span></span><span class="spanstar">&#9733</span></label>

                    <input id="widget_stars_rate_4" type="radio" name="widget_stars_rate" value="4" class="visuallyhidden">
                    <label for="widget_stars_rate_4" class="widget_label"><span class="visuallyhidden">4 <span class="widgetStrings">STARS</span></span><span class="spanstar">&#9733</span></label>

                    <input id="widget_stars_rate_5" type="radio" name="widget_stars_rate" value="5" class="visuallyhidden">
                    <label for="widget_stars_rate_5" class="widget_label"><span class="visuallyhidden">5 <span class="widgetStrings">STARS</span></span><span class="spanstar">&#9733</span></label>
                </p>
                
                <label for="widget_title_comment"><span class="widgetStrings">LABEL REVIEW TITLE</span></label>
                <input type="text" name="widget_title_comment" id="widget_title_comment"/>
                
                <label for="widget_comment"><span class="widgetStrings">LABEL REVIEW BODY</span></label>
                <textarea rows="2" cols="32" name="widget_comment" id="widget_comment"></textarea>
                <div aria-live="polite" class="errors" id="errors"></div>
                <p class="aligncenter">
                    <button href="#" class="red_button" id="buttonBack"><span class="widgetStrings">BACK</span></button>
                    <button class="blue_button" id="buttonSend"><span class="widgetStrings">SEND</span></button>
                </p>
            </form>
        </div>
        <div id="provideoyourrateok" tabindex="-1">
            <p><span class="widgetStrings">MESSAGE REVIEW OK</span></p>
            <p><a href="#" class="blue_button" id="buttonOk">Ok</a></p>
        </div>
        <?php if(user_is_logged_in()): ?>
            <p id="buttonprovideoyourrate">
                <a href="#" class="red_button" id="buttonDelete"><span class="widgetStrings">DELETE</span></a>
                <a href="#" class="blue_button" id="buttonRate"><span class="widgetStrings">CREATE</span></a>
            </p>
        <?php endif; ?>
    </div>
    <div id="about" style="display:none;">
        <a href="https://github.com/iluaepidi/rating-tool"><img style="position: absolute; top: 0; right: 0; border: 0;" src="https://camo.githubusercontent.com/38ef81f8aca64bb9a64448d0d70f1308ef5341ab/68747470733a2f2f73332e616d617a6f6e6177732e636f6d2f6769746875622f726962626f6e732f666f726b6d655f72696768745f6461726b626c75655f3132313632312e706e67" alt="Fork me on GitHub" data-canonical-src="https://s3.amazonaws.com/github/ribbons/forkme_right_darkblue_121621.png"></a>
        <p><img src="<?php print $GLOBALS['base_url'] . '/' . drupal_get_path('module', 'p4a_widget_client'); ?>/img/euroflag.jpg" alt=""/> Made by ILUNION for the Prosperity4All project: Ecosystem infrastructure for smart and personalised inclusion and PROSPERITY for ALL stakeholders. This project has received funding from the European Union’s Seventh Programme for research, technological development and demonstration under grant agreement, No 610510.</p>
    </div>
</div>