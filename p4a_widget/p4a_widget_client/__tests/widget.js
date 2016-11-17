describe('Widget', function(){
	
	jasmine.getFixtures().fixturesPath = './';
	jasmine.getStyleFixtures().fixturesPath = 'src/css/';
    if(typeof standalone != 'undefined' && standalone){
        jasmine.getFixtures().fixturesPath = './';
        jasmine.getStyleFixtures().fixturesPath = './../css/';
    }

	var html = readFixtures('ul.html');
	var widget_regex = /<section id=\"widget\"[^>]*>((.|[\n\r])*)<\/section>/im;
	var array_matches = widget_regex.exec(html);
	var widget_html = array_matches[0];

	
	beforeEach(function() {
		loadStyleFixtures('widget.css');
		setFixtures(widget_html);
		jasmine.Ajax.install();
		spyOn(WidgetUI, 'setWidgetStateWithRate').and.callThrough();
		spyOn(WidgetAPI, 'getAverageAndComments').and.callThrough();
		spyOn(WidgetAPI, 'doRequest').and.callThrough();
		spyOn($, 'ajax').and.callFake(function(options){
			options.success({value:3, comments:[]});
		});
		spyOn(WidgetUI, 'setWidgetStateCallback').and.callThrough();
		WidgetUI.initWidget();
	});

	afterEach(function() {
		jasmine.Ajax.uninstall();
	});
	
	describe('Initialization', function(){
		
		it('Should call WidgetUI.setWidgetStateWithRate', function(){
			expect(WidgetUI.setWidgetStateWithRate).toHaveBeenCalled();
		});
		
		it('Should initialize events', function(){
			expect($('#morecomments')).toHandle('click');
			expect($('#buttonRate')).toHandle('click');
			expect($('#buttonBack')).toHandle('click');
			expect($('#buttonOk')).toHandle('click');
			expect($('#buttonSend')).toHandle('click');
			expect($('#buttonDelete')).toHandle('click');
			//expect($('#buttonHistogram')).toHandle('click');
		});
		
		it('Should call WidgetAPI.getAverageAndComments', function(){
			expect(WidgetAPI.getAverageAndComments).toHaveBeenCalledWith(WidgetUI.setWidgetStateCallback);
		});
		
		it('Should call WidgetAPI.doRequest', function(){
			var preferences = {
				'id':WidgetConf.id,
				'app':WidgetConf.app,
				'user':WidgetConf.user,
				'grvalue':'0'
			};
			expect(WidgetAPI.doRequest).toHaveBeenCalledWith('ControllerGetStar', preferences, WidgetUI.setWidgetStateCallback);
		});
		
		it('Should call WidgetUI.setWidgetStateCallback', function(){
			expect(WidgetUI.setWidgetStateCallback).toHaveBeenCalledWith({value:3,comments:[]});
		});
		
	});
	
	describe('Initial state', function(){
		it('Should have a rate of 3', function(){
			expect($('#valuemedia a')).toContainText('0 ' + WidgetConf.strings('CUSTOMER REVIEW'));
			//expect($("#widget_stars_value_3")).toBeChecked();
		});
		
		it('Should show comments whit valoration of All', function(){
			expect(WidgetUI.activeRate).toBe('0');
		});
		
		it('Should have one comment', function(){
			expect('#widget_comments_ul > li').toHaveLength(1);
		});
		
		it('Should show first comment only', function(){
			expect('#widget_comments_ul > li:first-child').toBeVisible();
			expect($('#morecomments')).toBeHidden();
			expect($('#morecomments')).toContainText('Less Comments');
		});
		
		it('Rate form should be hidden and ratting button visible', function(){
			expect($('#provideoyourrate')).toBeHidden();
			expect($('#buttonprovideoyourrate')).toBeVisible();
			expect($('#buttonRate')).toContainText(WidgetConf.strings('CREATE'));
		});
		
		it('Button delete comment should be hidden', function(){
			expect($('#buttonDelete')).toBeHidden();
		});
	});
	
	describe('Initial state with a user\'s comment', function(){
	
		beforeEach(function(){
			var data = {
				value:3, 
				comments: [
					{title: '', comment: '', user: '4', value: 3, userComment:true, replies:[]},
					{title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]}
				]
			};
			WidgetUI.setWidgetStateCallback(data);
		});
		
		it('Should have two comments', function(){
			expect('#widget_comments_ul > li').toHaveLength(2);
		});
		
		it('Rate form should be hidden and ratting button should be edit comment', function(){
			expect($('#provideoyourrate')).toBeHidden();
			expect($('#buttonprovideoyourrate')).toBeVisible();
			expect($('#buttonRate')).toContainText(WidgetConf.strings('UPDATE'));
		});
		
		it('Button delete should be visible', function(){
			expect($('#buttonDelete')).toBeVisible();
		});
		
	});
	
	describe('Initial state with no user\'s comment', function(){
	
		beforeEach(function(){
			var data = {
				value:3, 
				comments: [
					{title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]},
					{title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]}
				]
			};
			WidgetUI.setWidgetStateCallback(data);
		});
		
		it('Should have two comments', function(){
			expect('#widget_comments_ul > li').toHaveLength(2);
		});
		
		it('Rate form should be hidden and ratting button visible', function(){
			expect($('#provideoyourrate')).toBeHidden();
			expect($('#buttonprovideoyourrate')).toBeVisible();
			expect($('#buttonRate')).toContainText(WidgetConf.strings('CREATE'));
		});
		
		it('Button delete should be hidden', function(){
			expect($('#buttonDelete')).toBeHidden();
		});
		
	});
	
	describe('Write a comment and rate it', function(){
		
		beforeEach(function(){
			spyOn(WidgetUI, 'provideRate').and.callThrough();
			ButtonRate = spyOnEvent('#buttonRate', 'click');
			$('#buttonRate').click();
		});
		
		it('Button rate click should be triggered, event stopped and WidgetUI.provideRate called', function(){
			expect(ButtonRate).toHaveBeenTriggered();
			expect(ButtonRate).toHaveBeenStopped();
			expect(WidgetUI.provideRate).toHaveBeenCalled();
		});
		
		it('Should show rate form and hide write comment button, comments and show comments', function(){
			expect($('#provideoyourrate')).toBeVisible();
			expect($('#listComments')).toBeHidden();
			expect($('#buttonRate')).toBeHidden();
			expect($('#buttonDelete')).toBeHidden();
			expect($('#morecomments')).toBeHidden();
		});
		
		it('Title and comment should be empty', function(){
			expect($('#widget_title_comment')).toHaveValue('');
			expect($('#widget_comment')).toHaveValue('');
		});
		
		it('Rate should have value of 1', function(){
			expect($('#widget_stars_rate_1')).toBeChecked();
		});
	});
	
	describe('Sends comment and rate', function(){
		
		beforeEach(function(){
			spyOn(WidgetUI, 'addRateAndComment').and.callThrough();
			spyOn(WidgetAPI, 'setRateAndComment').and.callThrough();
			spyOn(WidgetUI, 'addRateAndCommentCallback').and.callThrough();
			spyOn(WidgetUI, 'resetWidget').and.callThrough();
			ButtonSend = spyOnEvent('#buttonSend', 'click');
			ButtonOk = spyOnEvent('#buttonOk', 'click');
			$('#buttonRate').click();
			$('#widget_stars_rate_3').attr('checked', true);
			$('#widget_title_comment').val('Title');
			$('#widget_comment').val('Comment');
		});
		
		it('Should have form elements filled', function(){
			expect($('#widget_title_comment')).toHaveValue('Title');
			expect($('#widget_comment')).toHaveValue('Comment');
			expect($('#widget_stars_rate_3')).toBeChecked();
		});
		
		it('Send button should be clicked, WidgetUI.addRateAndComment and WidgetAPI.setRateAndComment called', function(){
			$('#buttonSend').click();
			expect(ButtonSend).toHaveBeenTriggered();
			expect(WidgetUI.addRateAndComment).toHaveBeenCalled();
			expect(WidgetAPI.setRateAndComment).toHaveBeenCalledWith('3', 'Title', 'Comment', WidgetUI.addRateAndCommentCallback);
		});
		
		it('Should call WidgetUI.addRateAndCommentCallback', function(){
			$('#buttonSend').click();
			expect(WidgetUI.addRateAndCommentCallback).toHaveBeenCalledWith({value:3,comments:[]});
		});
		
		it('Should show Thank you text and OK button', function(){
			$('#buttonSend').click();
			expect(WidgetUI.setWidgetStateWithRate).toHaveBeenCalled();
			expect($('#provideoyourrate')).toBeHidden();
			expect($('#provideoyourrateok')).toBeVisible();
			expect($('#provideoyourrateok')).toBeFocused();
		});
		
		it('Should reset interface after clicking OK button', function(){
			$('#buttonSend').click();
			$('#buttonOk').click();
			expect(ButtonOk).toHaveBeenTriggered();
			expect(WidgetUI.resetWidget).toHaveBeenCalled();
			expect($('#buttonprovideoyourrate')).toBeVisible();
			expect($('#provideoyourrateok')).toBeHidden();
			expect($('#morecomments')).toContainText('Less Comments');
		});
		
	});
	
	describe('Delete button', function(){
		beforeEach(function(){
			spyOn(WidgetUI, 'deleteRate').and.callThrough();
			spyOn(WidgetAPI, 'deleteRateAndComment').and.callThrough();
			spyOn(WidgetUI, 'deleteRateCallback').and.callThrough();
			ButtonDelete = spyOnEvent('#buttonDelete', 'click');
			$('#buttonDelete').click();
		});
		
		it('Should click button delete', function(){
			expect(ButtonDelete).toHaveBeenTriggered();
		});
		
		it('Should call, WidgetUI.deleteRate, WidgetApi.deleteRateAndComment and WidgetApi.deleteRateCallback', function(){
			expect(ButtonDelete).toHaveBeenTriggered();
			expect(WidgetUI.deleteRate).toHaveBeenCalled();
			expect(WidgetAPI.deleteRateAndComment).toHaveBeenCalledWith(WidgetUI.deleteRateCallback);
			expect(WidgetUI.deleteRateCallback).toHaveBeenCalled();
		});
		
		it('Should refresh the widget', function(){
			expect(WidgetUI.setWidgetStateWithRate).toHaveBeenCalled();
		});
		
	});
	
	describe('Histogram', function(){
		
		beforeEach(function(){
			var data = {
				value:3, 
				comments: [
					{title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]},
					{title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]}
				]
			};
			WidgetUI.setWidgetStateCallback(data);
			//ButtonHistogram = spyOnEvent('#buttonHistogram', 'click');
		});
		
		it('Should be hidden on init', function(){
			//expect($('#histogram table')).toBeHidden();
			expect($('#histogram')).toHaveClass('visuallyhidden');
		});
		/*
		it('Should show histogram on click', function(){
			$('#buttonHistogram').click();
			expect(ButtonHistogram).toHaveBeenTriggered();
			expect($('#histogram table')).toBeVisible();
		});
		*/
		it('Should have 100% value in 3 stars', function(){
			expect($('#histogram table tr:nth-child(3) td')).toContainText('100.00%');
		});
		/*
		it('Should hide on click if opened', function(){
			$('#buttonHistogram').click();
			expect(ButtonHistogram).toHaveBeenTriggered();
			$('#buttonHistogram').click();
			expect(ButtonHistogram).toHaveBeenTriggered();
			expect($('#histogram table')).toBeHidden();
		});
		*/
	});
	
	describe('Reply comment', function(){
		
		beforeEach(function(){
			var data = {
				value:3, 
				comments: [
					{title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]},
					{title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]}
				]
			};
			WidgetConf.isVendor = true;
			WidgetUI.setWidgetStateCallback(data);
			ButtonReply = spyOnEvent('#widget_comments_ul > li .reply_button', 'click');
		});
		
		it('Should have a reply button', function(){
			expect($('#widget_comments_ul > li .reply_button')).toContainText(WidgetConf.strings('REPLY'));
		});
		
		it('Should show reply form on click', function(){
			$('#widget_comments_ul > li:first-child .reply_button').click();
			expect(ButtonReply).toHaveBeenTriggered();
			expect($('#widget_comments_ul > li:first-child form .cancel')).toContainText(WidgetConf.strings('CANCEL'));
			expect($('#widget_comments_ul > li:first-child form .send')).toContainText(WidgetConf.strings('SEND'));
		});
	});
	
	describe('Like', function(){
		
		beforeEach(function(){
			var data = {
				value:3, 
				comments: [
					{id: '1', title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]},
					{id: '2', title: '', comment: '', user: '1', value: 3, userComment:false, replies:[]}
				]
			};
			WidgetUI.setWidgetStateCallback(data);
			spyOn(WidgetUI, 'likeComment').and.callThrough();
			spyOn(WidgetAPI, 'setCommentLike').and.callThrough();
			spyOn(WidgetUI, 'likeCommentCallback').and.callThrough();
			ButtonLike = spyOnEvent('#widget_comments_ul > li .like', 'click');
		});
		
		it('Should have a like button', function(){
			expect($('#widget_comments_ul > li .like')).toBeVisible();
		});
		
		it('Should like comment on click', function(){
			$('#widget_comments_ul > li:first-child .like').click();
			expect(ButtonLike).toHaveBeenTriggered();
			expect(WidgetUI.likeComment).toHaveBeenCalled();
			expect(WidgetAPI.setCommentLike).toHaveBeenCalledWith('1', WidgetUI.likeCommentCallback);
			expect(WidgetUI.likeCommentCallback).toHaveBeenCalled();
		});
	});
	
});