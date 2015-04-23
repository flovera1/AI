public class DebtProperty extends AbstractProperty{
	public static final String DEBT = "Debt";
	public static final String HIGH = "high";
	public static final String LOW  = "low";
	public DebtProperty(String value){
		super(value);
	}
	public final String getName(){
		return DEBT;
	}
}