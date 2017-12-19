$(function() {
    $('[data-toggle="tooltip"]').tooltip();
});

$(function() {
    $('[data-toggle="popover"]').popover();
});

$(window).on('resize', function() {
    if($(window).width() > 600) {
        $('#img').addClass('img-rounded');
        $('#img').removeClass('img-circle');
    }else{
        $('#img').addClass('img-circle');
        $('#img').removeClass('img-rounded');
    }
})

