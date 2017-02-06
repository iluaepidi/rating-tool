/**
 * Widget
 * Conf, API, UI, Init
 */

(function($){
    var WidgetAPI = {
        doRequest: function(controller, preferences, callback){
            $.ajax({
                url: WidgetConf.url + controller,
                type: 'get',
                data: preferences,
                dataType: 'json',
                async: true,
                crossDomain: true,
                xhrFields: {
                    withCredentials: false
                },
                success: function(data){
                    callback(data);
                },
                error: function(xhr, msg){
                    $('.widget_stars').text('Rating server conection error');
                    console.log(msg + ', ' + xhr.status + ': ' + xhr.statusText);
                }
            });
        },
        getAverageAndComments: function(callback){
            var preferences = {
                'id':WidgetConf.id,
                'app':WidgetConf.app,
                'user':WidgetConf.user,
                'grvalue':'0'
            };
            WidgetAPI.doRequest('ControllerGetStar', preferences, callback);
        },
        setRateAndComment: function(rate, title, comment, callback){
            var preferences = {
                'id':WidgetConf.id,
                'app':WidgetConf.app,
                'user':WidgetConf.user,
                'star':rate,
                'titlecomment': title,
                'comment': comment
            };
            WidgetAPI.doRequest('ControllerStar', preferences, callback);
        },
        deleteRateAndComment: function(callback){
            var preferences = {
                'id':WidgetConf.id,
                'app':WidgetConf.app,
                'user':WidgetConf.user
            };
            WidgetAPI.doRequest('ControllerDeleteStar', preferences, callback);
        },
        setCommentLike: function(IdComment, callback){
            var preferences = {
                'IdComment':IdComment,
                'user':WidgetConf.user
            };
            WidgetAPI.doRequest('ControllerRateComment', preferences, callback);
        },
        setReplyToComment: function(IdReply, IdComment, comment, callback){
            var preferences = {
                'IdReply':IdReply,
                'IdComment':IdComment,
                'user':WidgetConf.user,
                'comment': comment
            };
            WidgetAPI.doRequest('ControllerReplyComment', preferences, callback);
        },
        deleteReply: function(IdReply, callback){
            var preferences = {
                'IdReply':IdReply
            };
            WidgetAPI.doRequest('ControllerDeleteReply', preferences, callback);
        },
        setCommentFlag: function(IdComment, callback){
            var preferences = {
                'IdComment':IdComment,
                'user':WidgetConf.user
            };
            WidgetAPI.doRequest('ControllerFlagComment', preferences, callback);
        }
    };

    var WidgetUI = {
        
        init:true,
        activeRate : '0',
        timer:null,
        
        initWidget: function(){
            /* Check jQuery version. Needed for Drupal. jquey update dependencie.*/
            var version_numbers = $.fn.jquery.split('.');
            if(parseInt(version_numbers[0]) <= 1 && parseInt(version_numbers[1]) < 7){
                $('.widget_stars').text('Your jQuery version is out of date, widget module needs at less jQuery >= 1.7');
                return;
            }
            WidgetUI.setWidgetStateWithRate('0');
            
            $('#morecomments').on('click', function(){
                WidgetUI.moreComments();
                return false;
            });
            
            $('#buttonRate').on('click', function(){
                WidgetUI.provideRate();
                return false;
            });
            
            $('#buttonBack, #buttonOk').on('click', function(){
                WidgetUI.resetWidget();
                return false;
            });
            
            $('#buttonSend').on('click', function(){
                WidgetUI.addRateAndComment();
                return false;
            });
            /*
            $('#buttonDelete').on('click', function(){
                WidgetUI.deleteRate();
                return false;
            });
            */
            $('#buttonDelete').modaal({
                type: 'confirm',
                confirm_button_text: WidgetConf.strings('CONFIRM'),
                confirm_cancel_button_text: WidgetConf.strings('CANCEL'),
                confirm_title: WidgetConf.strings('CONFIRM ACTION'),
                confirm_content: '<p>' + WidgetConf.strings('DELETE CONFIRM') + '</p>',
                confirm_callback: function() {
                    WidgetUI.deleteRate();
                    return false;
                },
                confirm_cancel_callback: function() {
                    return false;
                }
            });

            $('#rate, #histogram').on('mouseover', function(){
                WidgetUI.showHistogram();
            }).on('mouseout', function(){
                WidgetUI.hideHistogram();
            });
            
            $('#rate, #histogram a').on('focus', function(){
                WidgetUI.showHistogram();
            }).on('blur', function(){
                WidgetUI.hideHistogram();
            });
            
            $('#histogram table a').on('click', function(){
				var real_rate = [5, 4, 3, 2, 1];
				var rate = real_rate[$(this).parents('tr').index()];
                WidgetUI.setWidgetStateWithRate(rate);
                return false;
            });
            
            /* New interface  ¿Integration? */
            $('#widget_stars_rate_part #rate, #widget_stars_comments_part #histogram').off('mouseover mouseout focus blur').find('a').off('focus blur');
            $('#widget_stars_comments_part #histogram a').on('focus', function(){
                $(this).parents('tr').addClass('hover');
            }).on('blur', function(){
                $(this).parents('tr').removeClass('hover');
            });
            
            //Event delegation
            $('#listComments').on('click', 'a.like_button', function(){
                var IdComment = $(this).data('IdComment');
                WidgetUI.likeComment(IdComment);
                return false;
            });
            $('#listComments').on('click', 'a.reply_button', function(){
                var IdComment = $(this).data('IdComment');
                WidgetUI.replyComment(IdComment);
                return false;
            });
            $('#listComments').on('click', '.cancel', function(){
                WidgetUI.removeReplyForm();
                return false;
            });
            $('#listComments').on('click', '.send', function(){
                WidgetUI.addReplyToComment();
                return false;
            });
            $('#listComments').on('click', '.edit_reply', function(){
                var IdReply = $(this).data('IdReply');
                var IdComment = $(this).data('IdComment');
                WidgetUI.editReply(IdReply, IdComment);
                return false;
            });
            /*
            $('#listComments').on('click', '.delete_reply', function(){
                var IdReply = $(this).data('IdReply');
                WidgetUI.deleteReply(IdReply);
                return false;
            });
            */
            /*
            $('#listComments').on('click', 'a.flag_button', function(){
                var IdComment = $(this).data('IdComment');
                WidgetUI.flagComment(IdComment);
                return false;
            });
            */
            $('.widgetStrings').text(function(index, oldText){
                return WidgetConf.strings(oldText);
            });
            
            $('.about .inline').modaal({
                hide_close: false
            });
        },
        setWidgetStateWithRate: function(rate){
            this.activeRate = rate;
            WidgetAPI.getAverageAndComments(WidgetUI.setWidgetStateCallback);
        },
        setWidgetStateCallback: function(data){
            var ncomments = data.comments.length > 1 ? WidgetConf.strings('CUSTOMER REVIEWS') : WidgetConf.strings('CUSTOMER REVIEW');
            var rating_text = '' + data.value + ' ' + WidgetConf.strings('OUT OF') + ' 5 ' + WidgetConf.strings('STARS');
            var review_test = '<a href="#widget_stars_comments_part">' + data.comments.length + ' ' + ncomments + '</a>';
            $("#starstext").html(rating_text);
            $("#valuemedia").html(review_test);
            var stars_rate = '';
			var int_part = Math.floor(data.value);
			var dec_part = (data.value % 1);
			var res_part = 5 - int_part - Math.ceil(dec_part);
			for(var i = 1; i <= int_part; i++){
				stars_rate += '<i class="fa fa-star"></i>';
			}
			if(dec_part > 0){
				stars_rate += '<i class="fa fa-star-half-o"></i>';
			}
			for(var i = 1; i <= res_part; i++){
				stars_rate += '<i class="fa fa-star-o"></i>';
			}
			/*
            for(var i = 1; i <= 5; i++){
                stars_rate += (i <= data.value) ? '&#9733;' : '&#9734;';
            }
			*/
            $("#valuemedia_stars").html(stars_rate);
            $('#review_stars').html('<span class="stars">' + stars_rate + '</span> <span class="visuallyhidden">' + rating_text + '</span> ' + $('#valuemedia a').text());
            $("#widget_comments_ul").empty();
            WidgetUI.setAddEditComment(false);
            $("#morecomments").show();
            if(data.comments.length){
                var n = 0;
                $.each(data.comments, function(i){
                    if(WidgetUI.activeRate == '0' || this.value == WidgetUI.activeRate){
                        n++;
                        if(this.user == WidgetConf.user){
                            WidgetUI.setAddEditComment(true);
                        }
                        WidgetUI.addComment(this);
                    }
                });
                
                if(n == 0){
                    WidgetUI.setNoComments(WidgetUI.activeRate);
                }
                if(n <= WidgetConf.commentsOnInit){
                    $("#morecomments").hide();
                }
            }
            else{
                WidgetUI.setNoComments(0);
            }
            if(WidgetUI.init){
                WidgetUI.init = false;
                WidgetUI.moreComments();
            }
            WidgetUI.setHistogram(data.comments);
        },
        addRateAndComment: function(){
            $('#errors p').remove();
            var rate = $('input[name=widget_stars_rate]:checked').val();
            if(typeof rate !== 'undefined'){
                var title = $('#widget_title_comment').val();
                var comment = $('#widget_comment').val();
                if(title != '' && comment != ''){
                    WidgetAPI.setRateAndComment(rate, title, comment, WidgetUI.addRateAndCommentCallback);
                }
                else{
                    //alert('Please write a title and comment');
                    $('#errors').append($('<p>').text(WidgetConf.strings("EMPTY FIELDS")));
                }
            }
            else{
                /*@todo:set errors on widget itself, don't use an alert */
                alert('You must select a rating from 1 to 5 stars');
            }
        },
        addRateAndCommentCallback: function(){
            WidgetUI.setWidgetStateWithRate('0');
            $("#provideoyourrate").hide();
            $("#provideoyourrateok").show();
            $("#provideoyourrateok").focus();
        },
        moreComments: function(){
            if($('#listComments > ul > li').eq(WidgetConf.commentsOnInit).is(':hidden')){
                $("#morecomments").text(WidgetConf.strings("LESS COMMENTS")).removeClass('more').addClass('less');
                $('#listComments > ul > li').show();
            }
            else{
                $("#morecomments").text(WidgetConf.strings("MORE COMMENTS")).removeClass('less').addClass('more');
                //$('#listComments > ul > li:not(:first-child)').hide();
                $('#listComments > ul > li').each(function(i){
                    if(i >= WidgetConf.commentsOnInit){
                        $(this).hide();
                    }
                });
            }
            $('#buttonprovideoyourrate').show();
        },
        provideRate: function(){
            $('#buttonprovideoyourrate').hide();
            $('#provideoyourrate').show();
            $('#listComments').hide();
            $('#morecomments').hide();
            $("#widget_title_comment").val('');
            $("#widget_comment").val('');
            $("#widget_stars_rate_1").focus();
        },
        editRate: function(){
            $('#buttonprovideoyourrate').hide();
            $('#provideoyourrate').show();
            $('#listComments').hide();
            $('#morecomments').hide();
            var title = $('#listComments li.user-' + WidgetConf.user + ' strong span').eq(0).text();
            $("#widget_title_comment").val(title);
            var comment = $('#listComments li.user-' + WidgetConf.user + ' > div').text();
            $("#widget_comment").val(comment);
            $("#widget_stars_rate_1").focus();
        },
        deleteRate: function(){
            WidgetAPI.deleteRateAndComment(WidgetUI.deleteRateCallback);
        },
        deleteRateCallback: function(){
            WidgetUI.setWidgetStateWithRate('0');
        },
        resetWidget: function(){
            $('#errors p').remove();
            $('#buttonprovideoyourrate').show();
            $('#listComments').show();
            $('#provideoyourrate').hide();
            $('#provideoyourrateok').hide();
            if($('#listComments li').length > 1){
                $('#morecomments').show();
            }
        },
        showHistogram: function(){
            clearTimeout(WidgetUI.timer);
            $('#histogram').removeClass('visuallyhidden');
        },
        hideHistogram: function(){
            WidgetUI.timer = setTimeout(function(){
                $('#histogram').addClass('visuallyhidden');
            }, 500);
        },
        setHistogram: function(data){
            var histogram = [
                {votes:0, percent:0},
                {votes:0, percent:0},
                {votes:0, percent:0},
                {votes:0, percent:0},
                {votes:0, percent:0}
            ];
            for(var i = 0; i < data.length; i++){
                histogram[data[i].value - 1].votes++;
                histogram[data[i].value - 1].percent = histogram[data[i].value - 1].votes * 100 / data.length;
            }
            histogram.reverse();
            for(var i = 0; i < histogram.length; i++){
                $('#histogram table tr').eq(i).find('td').html(
                    $('<div>').append($('<span>').css({width: histogram[i].percent + '%'}).html('&nbsp;'))
                ).append(histogram[i].percent.toFixed(2) + '%');
            }
        },
        likeComment: function(IdComment){
            WidgetAPI.setCommentLike(IdComment, WidgetUI.likeCommentCallback);
        },
        likeCommentCallback: function(data){
            WidgetUI.setWidgetStateWithRate('0');
        },
        setAddEditComment: function(edit){
            if(edit){
                $('#buttonRate').off('click').text(WidgetConf.strings('UPDATE')).on('click', function(){
                    WidgetUI.editRate();
                    return false;
                });
                $('#buttonDelete').show();
            }
            else{
                $('#buttonRate').off('click').text(WidgetConf.strings('CREATE')).on('click', function(){
                    WidgetUI.provideRate();
                    return false;
                });
                $('#buttonDelete').hide();
            }
        },
        setNoComments: function(n){
			if(parseInt(n) != 0){
				var li = $('<li>').html('<strong>There are no comments with ' + n + ' stars rate yet</strong>');
			}
			else{
				var li = $('<li>').html('<strong>There are no comments yet</strong>');
			}
            $("#widget_comments_ul").append(li);
            $("#morecomments").hide();
        },
        addComment: function(comment){
            var img = '<img src="' + comment.userImage + '" alt="" height="28" width="28">';
            var stars = '';
            for(var i = 1; i <= 5; i++){
                stars += (i <= comment.value) ? '&#9733;' : '&#9734;';
            }
            var stars_text = '<span class="visuallyhidden">' + comment.value + ' ' + WidgetConf.strings('OUT OF') + ' 5 ' + WidgetConf.strings('STARS') + '</span>';
            var title = '<strong><span>' + comment.title + '</span> ' + stars_text + stars + '</strong>';
            var user = '<span class="user"> ' + comment.userName + '</span>';
            var date = '<span class="date"> ' + new Date(comment.date).toLocaleDateString(WidgetConf.currentLocale()) + '</span>';
            var body = '<div>' + comment.c + '</div>';
            var html = img + title + '<br/>' + user + date + '<br />' + body;
            var li = $('<li>').html(html).addClass('user-' + comment.user).addClass('comment-' + comment.id).attr({tabIndex:0});
            if(!comment.userComment && WidgetConf.user != 0){
                var like = $('<a href="#" class="like_button"><span class="like"><span class="visuallyhidden">' + WidgetConf.strings('LIKE CONTENT') + '</span>&#10084;</span></a>').data({IdComment:comment.id});
            }
            else{
                var like = $('<span class="like">&#10084;</span>').data({IdComment:comment.id});
            }

            li.append(like);
            var likes = $('<span>').text(comment.rate);
            li.append(likes);
			li.append('&nbsp;<span class="visuallyhidden">' + WidgetConf.strings('LIKED CONTENT') + '</span>');
            //Flag
            if(WidgetConf.user != 0){
                if(!comment.userFlag){
                    var flag = $('<a href="#" class="flag_button"><span class="visuallyhidden">' + WidgetConf.strings('FLAG CONTENT') + '</span>&#9873;</a>').data({IdComment:comment.id});
                    flag.modaal({
                        type: 'confirm',
                        confirm_button_text: WidgetConf.strings('CONFIRM'),
                        confirm_cancel_button_text: WidgetConf.strings('CANCEL'),
                        confirm_title: WidgetConf.strings('CONFIRM ACTION'),
                        confirm_content: '<p>' + WidgetConf.strings('FLAG CONFIRM') + '</p>',
                        confirm_callback: function(){
                            var IdComment = this.options.IdComment;
                            WidgetUI.flagComment(IdComment);
                            return false;
                        },
                        confirm_cancel_callback: function() {
                            return false;
                        },
                        after_open: function(){
                            $('body > *:not(.modaal-wrapper)').attr('aria-hidden', true);
                        },
                        before_close: function(){
                            $('body > *:not(.modaal-wrapper)').removeAttr('aria-hidden');
                        }
                    });
                }
                else{
                    var flag = $('<span class="flag_button"><span class="visuallyhidden">' + WidgetConf.strings('FLAGED CONTENT') + '</span>&#9873;</span>').data({IdComment:comment.id});
                }
                li.append(flag);
            }
            //Vendor reply
            if(WidgetConf.isVendor){
                var reply = $('<a>').attr({href:'#'}).text(WidgetConf.strings('REPLY')).addClass('reply_button').data({IdComment:comment.id});
                li.append(reply);
            }
            //Replies
            if(comment.replies.length > 0){
                var ul_replies = $('<ul>');
                $.each(comment.replies, function(){
                    var li_reply = $('<li>').addClass('reply-' + this.id);
                    var reply_date = $('<span>').text(new Date(this.date).toLocaleDateString(WidgetConf.currentLocale())).addClass('date');
                    var reply_text = $('<p>').text(this.reply);
                    li_reply.append(reply_date);
                    li_reply.append(reply_text);
                    if(WidgetConf.isVendor && this.user == WidgetConf.user){
                        var reply_edit   = $('<a>').attr({href:'#'}).text(WidgetConf.strings('EDIT REPLY')).addClass('edit_reply blue_button').data({IdReply: this.id, IdComment: comment.id});
                        var reply_delete = $('<a>').attr({href:'#'}).text(WidgetConf.strings('DELETE REPLY')).addClass('delete_reply red_button').data({IdReply: this.id, IdComment: comment.id});
                        reply_delete.modaal({
                            type: 'confirm',
                            confirm_button_text: WidgetConf.strings('CONFIRM'),
                            confirm_cancel_button_text: WidgetConf.strings('CANCEL'),
                            confirm_title: WidgetConf.strings('CONFIRM ACTION'),
                            confirm_content: '<p>' + WidgetConf.strings('DELETE CONFIRM') + '</p>',
                            confirm_callback: function(){
                                var IdReply = this.options.IdReply;
                                WidgetUI.deleteReply(IdReply);
                                return false;
                            },
                            confirm_cancel_callback: function() {
                                return false;
                            }
                        });
                        li_reply.append(reply_delete);
                        li_reply.append(reply_edit);
                        //Remove Reply comment link
                        //Hide for backward compatibility
                        li.find('.reply_button').hide();
                    }
                    ul_replies.append(li_reply);
                });
                li.append(ul_replies);
            }
            $("#widget_comments_ul").append(li);
        },
        replyComment: function(IdComment){
            WidgetUI.addReplyForm(IdComment, 0);
        },
        addReplyForm: function(IdComment, IdReply){
            WidgetUI.removeReplyForm();
            var form = $('<form>');
            var textarea = $('<textarea>');
            if(IdReply != 0){
                var reply_text = $('#listComments li.comment-' + IdComment + ' li.reply-' + IdReply + ' p').text();
                textarea.text(reply_text);
            }
            var reply = $('<input>').attr({type:'hidden', name:'IdReply'}).val(IdReply);
            var comment = $('<input>').attr({type:'hidden', name:'IdComment'}).val(IdComment);
            var send = $('<button>').text('Send').addClass('send blue_button');
            var back = $('<button>').text('Cancel').addClass('cancel red_button');
            form.append(reply);
            form.append(comment);
            form.append(textarea);
            form.append(back);
            form.append(send);
            $('#listComments li.comment-' + IdComment + ' .reply_button').after(form);
        },
        removeReplyForm: function(){
            $('#listComments li form').remove();
        },
        addReplyToComment: function(){
            var IdReply = $('#listComments li form input[name=IdReply]').val();
            var IdComment = $('#listComments li form input[name=IdComment]').val();
            var comment = $('#listComments li form textarea').val();
            WidgetAPI.setReplyToComment(IdReply, IdComment, comment, WidgetUI.addReplyToCommentCallback);
        },
        addReplyToCommentCallback: function(){
            //WidgetUI.removeReplyForm();//¿needed?
            WidgetUI.setWidgetStateWithRate('0');
        },
        deleteReply: function(IdReply){
            WidgetAPI.deleteReply(IdReply, WidgetUI.deleteReplyCallback);
        },
        deleteReplyCallback: function(){
            WidgetUI.setWidgetStateWithRate('0');
        },
        editReply: function(IdReply, IdComment){
            WidgetUI.addReplyForm(IdComment, IdReply);
        },
        editReplyCallback: function(){
            alert('editReplyCallback');
        },
        flagComment: function(IdComment){
            WidgetAPI.setCommentFlag(IdComment, WidgetUI.flagCommentCallback);
        },
        flagCommentCallback: function(data){
            WidgetUI.setWidgetStateWithRate('0');
        }
    };

    $(document).ready(function(){
        WidgetUI.initWidget();
    });

})(jQuery);