// ������֮����Ҫ����������ť��״̬
function modeRobotDealBtnState(id,bDisabled,strDisplay){	
	var btnDeal = document.getElementById(id);
	if(!!btnDeal){
		btnDeal.disabled=bDisabled;
		btnDeal.innerHTML = strDisplay;
	}
}

